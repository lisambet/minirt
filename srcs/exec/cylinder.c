/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:36:03 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/12 15:08:01 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder *cylinder(t_point p0, t_vec normal, double diameter, double height, t_color color)
{
	t_cylinder *new;

	new = malloc(sizeof(t_cylinder));
	if (!new)
		return (NULL);
	new->p0 = p0;
	new->normal = normal;
	new->diameter = diameter;
	new->height = height;
	new->color.red = color.red / 255.0;
	new->color.green = color.green / 255.0;
	new->color.blue = color.blue / 255.0;
	new->next = NULL;
	return (new);
}

bool	solve_quadratic(double a, double b, double c, double *t1, double *t2)
{
	double	discriminant;
	double	q_sqrt;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	if (fabs(a) < 1e-6)
	{
		if (fabs(b) < 1e-6)
			return (false);
		*t1 = -c / b;
		*t2 = -1.0;
		return (true);
	}
	q_sqrt = sqrt(discriminant);
	*t1 = (-b - q_sqrt) / (2.0 * a);
	*t2 = (-b + q_sqrt) / (2.0 * a);
	return (true);
}

void	get_cyl_eq_coefficients(t_cylinder *cyl, t_ray r, double *a, double *b, double *c)
{
	t_vec	oc;
	t_vec	n;
	t_vec	d;

	oc = vec_sub(r.orig, cyl->p0);
	n = cyl->normal;
	d = r.dir;
	*a = vec_dot(d, d) - pow(vec_dot(d, n), 2);
	*b = 2.0 * (vec_dot(d, oc) - vec_dot(d, n) * vec_dot(oc, n));
	*c = vec_dot(oc, oc) - pow(vec_dot(oc, n), 2) - cyl->diameter * cyl->diameter;
}

double	get_m_projection(t_cylinder *cyl, t_ray r, double t)
{
	t_vec	oc;
	t_vec	n;
	t_vec	d;

	oc = vec_sub(r.orig, cyl->p0);
	n = cyl->normal;
	d = r.dir;
	return (vec_dot(d, n) * t + vec_dot(oc, n));
}

