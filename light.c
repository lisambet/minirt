/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:31:44 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/19 14:56:44 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_lgt *light(t_point vtx, float i, t_color color)
{
	t_lgt	*new;

	new = malloc(sizeof(t_lgt));
	if (!new)
		return (NULL);
	new->vtx = vtx;
	new->i = i;
	new->color.x = color.x / 255.0;
	new->color.y = color.y / 255.0;
	new->color.z = color.z / 255.0;
	new->next = NULL;
	return (new);
}
t_amb *amb(float i, t_color color)
{
	t_amb	*new;

	new = malloc(sizeof(t_amb));
	if (!new)
		return (NULL);
	new->i = i;
	new->color = color;
	return (new);
}

t_color light_objects(t_scene *s, t_ray r, void *object, int object_type, t_point intersection_point, double closest_t)
{
    t_vec normal;
    t_color object_color;
    t_lgt *light = s->lights;
    t_color final_color = (t_color){0, 0, 0};

    if (!light)
        return final_color;
    if (object_type == 0)
    {
        t_sphere *sp = (t_sphere *)object;
        normal = vec_normalize(vec_sub(intersection_point, sp->center));
        object_color = sp->color;
    }
    else if (object_type == 1)
    {
        t_plane *pl = (t_plane *)object;
        normal = pl->normal;
        object_color = pl->color;
    }
    else if (object_type == 2)
    {
        t_cylinder *cyl = (t_cylinder *)object;
        t_vec oc = vec_sub(intersection_point, cyl->p0);
        double m = vec_dot(r.dir, cyl->normal) * closest_t + vec_dot(vec_sub(r.orig, cyl->p0), cyl->normal);
        t_vec normal_unnormalized = vec_sub(oc, vec_mul(cyl->normal, m));
        normal = vec_normalize(normal_unnormalized);
        object_color = cyl->color;
    }
    else
        return final_color;
    t_vec light_dir = vec_normalize(vec_sub(light->vtx, intersection_point));
    double diffuse = fmax(vec_dot(normal, light_dir), 0);
    final_color.x = object_color.x * light->color.x * diffuse * light->i;
    final_color.y = object_color.y * light->color.y * diffuse * light->i;
    final_color.z = object_color.z * light->color.z * diffuse * light->i;
    return final_color;
}