/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:31:35 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/23 15:49:59 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_sphere(t_sphere *sp, t_ray r, double *t_out, double t)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec_sub(r.orig, sp->center);
	a = vec_dot(r.dir, r.dir);
	b = 2.0 * vec_dot(oc, r.dir);
	c = vec_dot(oc, oc) - sp->diameter * sp->diameter;
	discriminant = b * b - 4 * a * c;
	*t_out = 0;
	if (discriminant < 0)
		return (false);
	t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t > 0.001)
	{
		*t_out = t;
		return (true);
	}
	return (false);
}

bool	hit_plane(t_plane *plane, t_ray r, double *t_out)
{
	double	denom;
	double	t;

	denom = vec_dot(plane->normal, r.dir);
	if (fabs(denom) > 1e-6)
	{
		t = vec_dot(vec_sub(plane->p0, r.orig), plane->normal) / denom;
		if (t >= 0)
		{
			if (t_out)
				*t_out = t;
			return (true);
		}
	}
	return (false);
}

void	draw_blocks(t_scene *s, size_t x, size_t y, t_color color)
{
	size_t	tx;
	size_t	ty;

	ty = 0;
	while (ty < (size_t)SCALEDOWN && ty + y < (size_t)HEIGHT)
	{
		tx = 0;
		while (tx < (size_t)SCALEDOWN && tx + x < (size_t)WIDTH)
		{
			s->data[(y + ty) * WIDTH + (x + tx)] = get_color_int(color);
			tx++;
		}
		ty++;
	}
}
