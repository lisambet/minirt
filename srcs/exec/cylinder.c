/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:36:03 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/30 14:11:16 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	solve_quadratic(double indices[3], double *t1, double *t2)
{
	double	discriminant;
	double	q_sqrt;

	discriminant = indices[1] * indices[1] - 4 * indices[0] * indices[2];
	if (discriminant < 0)
		return (false);
	if (fabs(indices[0]) < 1e-6)
	{
		if (fabs(indices[1]) < 1e-6)
			return (false);
		*t1 = -indices[2] / indices[1];
		*t2 = -1.0;
		return (true);
	}
	q_sqrt = sqrt(discriminant);
	*t1 = (-indices[1] - q_sqrt) / (2.0 * indices[0]);
	*t2 = (-indices[1] + q_sqrt) / (2.0 * indices[0]);
	return (true);
}

void	get_cyl_eq_coefficients(t_cylinder *cyl, t_ray r, double *indices[3])
{
	t_vec	oc;
	t_vec	n;
	t_vec	d;

	oc = vec_sub(r.orig, cyl->p0);
	n = cyl->normal;
	d = r.dir;
	*indices[0] = vec_dot(d, d) - pow(vec_dot(d, n), 2);
	*indices[1] = 2.0 * (vec_dot(d, oc) - vec_dot(d, n) * vec_dot(oc, n));
	*indices[2] = vec_dot(oc, oc) - pow(vec_dot(oc, n), 2) - cyl->diameter  * 0.5
		* cyl->diameter  * 0.5;
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
