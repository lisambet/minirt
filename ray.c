/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:27:41 by lisambet          #+#    #+#             */
/*   Updated: 2025/04/22 21:19:46 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray ray(t_point3 origin, t_vec direction)
{
	t_ray r = {origin, direction};
	return r;
}

t_point3 ray_at(t_ray r, double t)
{
	return vec_add(r.orig, vec_mul(r.dir, t));
}

t_color ray_color(t_ray r)
{
	t_vec unit_dir = vec_unit(r.dir);
	double t = 0.5 * (unit_dir.y + 1.0);
	t_color white = vec(1.0, 1.0, 1.0);
	t_color blue = vec(0.5, 0.7, 1.0);
	return vec_add(vec_mul(white, (1.0 - t)), vec_mul(blue, t));
}

int get_color_int(t_color c)
{
	int r = (int)(255.999 * c.x);
	int g = (int)(255.999 * c.y);
	int b = (int)(255.999 * c.z);
	return (r << 16) | (g << 8) | b;
}
