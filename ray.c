/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:27:41 by lisambet          #+#    #+#             */
/*   Updated: 2025/04/22 21:41:04 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
t_ray	ray(t_point3 origin, t_vec direction)
{
	t_ray	r;

	r.orig = origin;
	r.dir = direction;
	return (r);
}

t_point3	ray_at(t_ray r, double t)
{
	return (vec_add(r.orig, vec_mul(r.dir, t)));
}

t_color	ray_color(t_ray r)
{
	t_vec	unit_dir;
	double	t;
	t_color	white;
	t_color	blue;

	if (sphere(vec(0, 0, -1), 0.5, r))
		return (vec(1.0, 0.0, 0.0));
	unit_dir = vec_unit(r.dir);
	t = 0.5 * (unit_dir.y + 1.0);
	white = vec(1.0, 1.0, 1.0);
	blue = vec(0.5, 0.7, 1.0);
	return (vec_add(vec_mul(white, (1.0 - t)), vec_mul(blue, t)));
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
