/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:31:35 by lisambet          #+#    #+#             */
/*   Updated: 2025/04/26 13:02:08 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	sphere(t_point center, double radius, t_ray r)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec_sub(r.orig, center);
	a = vec_dot(r.dir, r.dir);
	b = -2.0 * vec_dot(r.dir, oc);
	c = vec_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}
bool plane(t_point p0, t_vec normal, t_ray r)
{
	double denom;
	double t;

	denom = vec_dot(normal, r.dir);
	if (fabs(denom) > 1e-6)
	{
		t = vec_dot(vec_sub(p0, r.orig), normal) / denom;
		return (t >= 0);
	}
	return (false);
}
