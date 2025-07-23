/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:10:40 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/23 15:43:35 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_cylinder_side(t_cylinder *cyl, t_ray r, double *t_side, double m)
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;

	get_cyl_eq_coefficients(cyl, r, (double *[3]){&a, &b, &c});
	*t_side = -1.0;
	if (!solve_quadratic((double [3]){a, b, c}, &t1, &t2))
		return (false);
	if (t1 >= 0.001)
	{
		m = get_m_projection(cyl, r, t1);
		if (m >= 0 && m <= cyl->height)
			*t_side = t1;
	}
	if (t2 >= 0.001 && (*t_side < 0 || t2 < *t_side))
	{
		m = get_m_projection(cyl, r, t2);
		if (m >= 0 && m <= cyl->height)
			*t_side = t2;
	}
	return (*t_side > 0);
}

bool	hit_cylinder_top_cap(t_cylinder *cyl, t_ray r, double *t_top_cap,
		double t_closest[2])
{
	t_vec	n;
	t_point	p;
	t_point	top_center;
	double	t;
	double	denom;

	*t_top_cap = -1.0;
	n = cyl->normal;
	top_center = vec_add(cyl->p0, vec_mul(n, cyl->height));
	denom = vec_dot(r.dir, n);
	if (fabs(denom) > 1e-6)
	{
		t = vec_dot(vec_sub(top_center, r.orig), n) / denom;
		p = ray_at(r, t);
		if (t >= 0.001 && (t < t_closest[0] || t_closest[0] < 0)
			&& (t < t_closest[1] || t_closest[1] < 0)
			&& vec_length_sq(vec_sub(p, top_center)) <= (cyl->diameter
				* cyl->diameter) + 1e-6)
		{
			*t_top_cap = t;
			return (true);
		}
	}
	return (false);
}

bool	hit_cylinder_base_cap(t_cylinder *cyl, t_ray r, double *t_base_cap,
		double t_side_closest)
{
	t_vec	n;
	t_point	p;
	double	t;
	double	denom;

	*t_base_cap = -1.0;
	n = cyl->normal;
	denom = vec_dot(r.dir, vec_neg(n));
	if (fabs(denom) > 1e-6)
	{
		t = vec_dot(vec_sub(cyl->p0, r.orig), vec_neg(n)) / denom;
		p = ray_at(r, t);
		if (t >= 0.001 && (t < t_side_closest || t_side_closest < 0)
			&& vec_length_sq(vec_sub(p, cyl->p0)) <= (cyl->diameter
				* cyl->diameter) + 1e-6)
		{
			*t_base_cap = t;
			return (true);
		}
	}
	return (false);
}

void	update_closest_hit(double *t_current, int *type_current,
		double t_candidate, int type_candidate)
{
	if (t_candidate > 0 && t_candidate < *t_current)
	{
		*t_current = t_candidate;
		*type_current = type_candidate;
	}
}

bool	hit_cylinder(t_cylinder *cyl, t_ray r, double *t_out, int *hit_type)
{
	double	t_side;
	double	t_base_cap;
	double	t_top_cap;

	t_side = -1.0;
	t_base_cap = -1.0;
	t_top_cap = -1.0;
	hit_cylinder_side(cyl, r, &t_side, 0);
	hit_cylinder_base_cap(cyl, r, &t_base_cap, t_side);
	hit_cylinder_top_cap(cyl, r, &t_top_cap, (double [2]){t_side, t_base_cap});
	*t_out = INFINITY;
	*hit_type = -1;
	update_closest_hit(t_out, hit_type, t_side, 0);
	update_closest_hit(t_out, hit_type, t_base_cap, 1);
	update_closest_hit(t_out, hit_type, t_top_cap, 1);
	return (*t_out != INFINITY);
}
