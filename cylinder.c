/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:36:03 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/20 14:46:59 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder *cylinder(t_point p0, t_vec normal, double radius, double height, t_color color)
{
	t_cylinder *new;

	new = malloc(sizeof(t_cylinder));
	if (!new)
		return (NULL);
	new->p0 = p0;
	new->normal = normal;
	new->radius = radius;
	new->height = height;
	new->color.x = color.x / 255.0;
	new->color.y = color.y / 255.0;
	new->color.z = color.z / 255.0;
	new->next = NULL;
	return (new);
}

bool	hit_cylinder_cap(t_cylinder *cyl, t_ray r, double *t_cap, double t_side)
{
	t_vec	n;
	t_vec	d;
	t_point	p;
	t_point	top;
	double	t;
	double	denom;

	*t_cap = -1.0;
	n = cyl->normal;
	d = r.dir;
	denom = vec_dot(d, vec_neg(n));
	if (fabs(denom) > 1e-6)
	{
		t = vec_dot(vec_sub(cyl->p0, r.orig), vec_neg(n)) / denom;
		p = vec_add(r.orig, vec_mul(d, t));
		if (t >= 0.001 && (t < t_side || t_side < 0)
			&& vec_length(vec_sub(p, cyl->p0)) <= cyl->radius + 1e-6)
			*t_cap = t;
	}
	top = vec_add(cyl->p0, vec_mul(n, cyl->height));
	denom = vec_dot(d, n);
	if (fabs(denom) > 1e-6)
	{
		t = vec_dot(vec_sub(top, r.orig), n) / denom;
		p = vec_add(r.orig, vec_mul(d, t));
		if (t >= 0.001 && (t < *t_cap || *t_cap < 0)
			&& (t < t_side || t_side < 0)
			&& vec_length(vec_sub(p, top)) <= cyl->radius + 1e-6)
			*t_cap = t;
	}
	return (*t_cap > 0);
}

bool	hit_cylinder_side(t_cylinder *cyl, t_ray r, double *t_side)
{
	t_vec	oc;
	t_vec	n;
	t_vec	d;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
	double	m;

	oc = vec_sub(r.orig, cyl->p0);
	n = cyl->normal;
	d = r.dir;
	a = vec_dot(d, d) - pow(vec_dot(d, n), 2);
	b = 2.0 * (vec_dot(d, oc) - vec_dot(d, n) * vec_dot(oc, n));
	c = vec_dot(oc, oc) - pow(vec_dot(oc, n), 2)
		- cyl->radius * cyl->radius;
	discriminant = b * b - 4 * a * c;
	*t_side = -1.0;
	if (discriminant < 0)
		return (false);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 >= 0.001)
	{
		m = vec_dot(d, n) * t1 + vec_dot(oc, n);
		if (m >= 0 && m <= cyl->height)
			*t_side = t1;
	}
	if (t2 >= 0.001 && (*t_side < 0 || t2 < *t_side))
	{
		m = vec_dot(d, n) * t2 + vec_dot(oc, n);
		if (m >= 0 && m <= cyl->height)
			*t_side = t2;
	}
	return (*t_side > 0);
}


bool hit_cylinder(t_cylinder *cyl, t_ray r, double *t_out, int *hit_type)
{
    double t_side = -1.0;
    double t_cap = -1.0;
    bool hit_side_bool = hit_cylinder_side(cyl, r, &t_side);
    bool hit_cap_bool = hit_cylinder_cap(cyl, r, &t_cap, t_side);

    *t_out = -1.0;
    *hit_type = -1;

    if (hit_side_bool && hit_cap_bool)
    {
        if (t_side < t_cap)
        {
            *t_out = t_side;
            *hit_type = 0;
        }
        else
        {
            *t_out = t_cap;
            *hit_type = 1;
        }
        return (true);
    }
    else if (hit_side_bool)
    {
        *t_out = t_side;
        *hit_type = 0;
        return (true);
    }
    else if (hit_cap_bool)
    {
        *t_out = t_cap;
        *hit_type = 1;
        return (true);
    }
    return (false);
}

