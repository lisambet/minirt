/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:27:41 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/07 19:59:51 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
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

t_color	ray_color(t_sphere *spheres, t_plane *planes, t_cylinder *cylinders, t_ray r)
{
	double closest_t = INFINITY;
	t_color final_color = (t_color){0, 0, 0}; // Background: black

	while (spheres)
	{
		double t;
		if (hit_sphere(spheres, r, &t) && t < closest_t)
		{
			closest_t = t;
			final_color = spheres->color;
		}
		spheres = spheres->next;
	}
	while (planes)
	{
		double t;
		if (hit_plane(planes, r, &t) && t < closest_t)
		{
			closest_t = t;
			final_color = planes->color;
		}
		planes = planes->next;
	}
	while (cylinders)
	{
		double t;
		if (hit_cylinder(cylinders, r, &t) && t < closest_t)
		{
			closest_t = t;
			final_color = cylinders->color;
		}
		cylinders = cylinders->next;
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
