/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:31:35 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/07 19:42:54 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool hit_sphere(t_sphere *sp, t_ray r, double *t_out)
{
	t_vec oc = vec_sub(r.orig, sp->center);
	double a = vec_dot(r.dir, r.dir);
	double b = 2.0 * vec_dot(oc, r.dir);
	double c = vec_dot(oc, oc) - sp->radius * sp->radius;
	double discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return false;

	double t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t > 0.001) {
		*t_out = t;
		return true;
	}
	return false;
}
t_sphere *sphere(t_point center, double radius, t_color color)
{
	t_sphere	*new;

	new = malloc(sizeof(t_sphere));
	if (!new)
		return (NULL);
	new->center = center;
	new->radius = radius;
	new->color = color;
	new->next = NULL;
	return (new);
}
t_plane *plane(t_point p0, t_vec normal, t_color color)
{
	t_plane	*new;

	new = malloc(sizeof(t_plane));
	if (!new)
		return (NULL);
	new->p0 = p0;
	new->normal = normal;
	new->color = color;
	new->next = NULL;
	return (new);
}

t_cylinder *cylinder(t_point p0, t_vec normal, double radius, double height, t_color color)
{
	t_cylinder	*new;

	new = malloc(sizeof(t_cylinder));
	if (!new)
		return (NULL);
	new->p0 = p0;
	new->normal = normal;
	new->radius = radius;
	new->height = height;
	new->color = color;
	new->next = NULL;
	return (new);
}

bool hit_cylinder(t_cylinder *cyl, t_ray r, double *t_out)
{
	t_vec oc = vec_sub(r.orig, cyl->p0);
	double a = vec_dot(r.dir, r.dir) - pow(vec_dot(r.dir, cyl->normal), 2);
	double b = 2.0 * (vec_dot(oc, r.dir) - vec_dot(oc, cyl->normal) * vec_dot(r.dir, cyl->normal));
	double c = vec_dot(oc, oc) - pow(vec_dot(oc, cyl->normal), 2) - cyl->radius * cyl->radius;
	double discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return false;

	double t = (-b - sqrt(discriminant)) / (2.0 * a);
	if (t > 0.001) {
		*t_out = t;
		return true;
	}
	return false;
}

bool	hit_plane(t_plane *plane, t_ray r, double *t_out)
{
	double denom;
	double t;

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
