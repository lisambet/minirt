/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:27:41 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/12 18:39:39 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color color_add(t_color a, t_color b, float intensity) // plus doux
{
	return ((t_color){a.x * intensity + b.x * (1 - intensity),
		a.y * intensity + b.y * (1 - intensity),
		a.z * intensity + b.z * (1 - intensity)});
}

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

t_color	ray_color(t_scene *s, t_ray r)
{
	double closest_t = INFINITY;
	t_color final_color = (t_color){0, 0, 0};

	t_lgt *light = s->lights;
	while (light)
	{
		final_color = color_add(final_color, light->color, light->i);
		light = light->next;
	}
	t_sphere *sphere = s->spheres;
	while (sphere)
	{
		double t;
		if (hit_sphere(sphere, r, &t) && t < closest_t)
		{
			closest_t = t;
			final_color = color_add(sphere->color, s->amb->color, s->amb->i);
		}
		sphere = sphere->next;
	}
	t_plane *plane = s->planes;
	while (plane)
	{
		double t;
		if (hit_plane(plane, r, &t) && t < closest_t)
		{
			closest_t = t;
			final_color = color_add(plane->color, s->amb->color, s->amb->i);
		}
		plane = plane->next;
	}
	t_cylinder *cylinder = s->cylinders;
	while (cylinder)
	{
		double t;
		if (hit_cylinder(cylinder, r, &t) && t < closest_t)
		{
			closest_t = t;
			final_color = color_add(cylinder->color, s->amb->color, s->amb->i);
		}
		cylinder = cylinder->next;
	}
	return final_color;
}

int	get_color_int(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.999 * c.x);
	g = (int)(255.999 * c.y);
	b = (int)(255.999 * c.z);
	return ((r << 16) | (g << 8) | b);
}
