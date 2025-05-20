/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:27:41 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/20 14:46:31 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_color color_add(t_color a, t_color b, float intensity) // plus doux
// {
// 	return ((t_color){a.x * intensity + b.x * (1 - intensity),
// 		a.y * intensity + b.y * (1 - intensity),
// 		a.z * intensity + b.z * (1 - intensity)});
// }

t_ray	ray(t_point origin, t_vec direction)
{
	t_ray	r;

	r.orig = origin;
	r.dir = direction;
	return (r);
}

t_point	ray_at(t_ray r, double t)
{
	return (vec_add(r.orig, vec_mul(r.dir, t)));
}


void check_sphere_hits(t_scene *s, t_ray r, t_hit_record *rec)
{
    t_sphere *sphere = s->spheres;
    double current_t;

    while (sphere)
    {
        if (hit_sphere(sphere, r, &current_t) && current_t > 0.001 && current_t < rec->t)
        {
            rec->t = current_t;
            rec->p = ray_at(r, rec->t);
            rec->color = sphere->color;
            rec->object_ptr = sphere;
            rec->object_type = OBJ_SPHERE;
            rec->hit = 1;
        }
        sphere = sphere->next;
    }
}

void check_plane_hits(t_scene *s, t_ray r, t_hit_record *rec)
{
    t_plane *plane = s->planes;
    double current_t;

    while (plane)
    {
        if (hit_plane(plane, r, &current_t) && current_t > 0.001 && current_t < rec->t)
        {
            rec->t = current_t;
            rec->p = ray_at(r, rec->t);
            rec->color = plane->color;
            rec->object_ptr = plane;
            rec->object_type = OBJ_PLANE;
            rec->hit = 1;
        }
        plane = plane->next;
    }
}

void check_cylinder_hits(t_scene *s, t_ray r, t_hit_record *rec)
{
    t_cylinder *cylinder = s->cylinders;
    double current_t;
	int hit_type; 

    while (cylinder)
    {
        if (hit_cylinder(cylinder, r, &current_t, &hit_type) && current_t > 0.001 && current_t < rec->t)
        {
            rec->t = current_t;
            rec->p = ray_at(r, rec->t);
            rec->color = cylinder->color;
            rec->object_ptr = cylinder;
            rec->object_type = OBJ_CYLINDER;
            rec->hit = 1;
            rec->hit_type = hit_type;
        }
        cylinder = cylinder->next;
    }
}


