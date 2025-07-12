/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:31:35 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/12 15:06:51 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_sphere(t_sphere *sp, t_ray r, double *t_out)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;

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

t_sphere	*sphere(t_point center, double diameter, t_color color)
{
	t_sphere	*new;

	new = malloc(sizeof(t_sphere));
	if (!new)
		return (NULL);
	new->center = center;
	new->diameter = diameter;
	new->color.red = color.red / 255.0;
	new->color.green = color.green / 255.0;
	new->color.blue = color.blue / 255.0;
	new->next = NULL;
	return (new);
}

t_plane	*plane(t_point p0, t_vec normal, t_color color)
{
	t_plane	*new;

	new = malloc(sizeof(t_plane));
	if (!new)
		return (NULL);
	new->p0 = p0;
	new->normal = normal;
	new->color.red = color.red / 255.0;
	new->color.green = color.green / 255.0;
	new->color.blue = color.blue / 255.0;
	new->next = NULL;
	return (new);
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
