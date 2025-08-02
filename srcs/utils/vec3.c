/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:14:53 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/27 12:38:31 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vec_normalize(t_vec v)
{
	double	length;

	length = vec_length(v);
	if (length == 0)
		return (vec(0, 0, 0));
	return (vec_div(v, length));
}

t_vec	vec_cross(t_vec a, t_vec b)
{
	t_vec	result;

	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);
	return (result);
}

t_vec	rotate_vec(t_vec v, t_vec axis, double angle_deg)
{
	double	a;
	double	c;
	double	s;
	t_vec	cross;
	double	dot;

	a = angle_deg * PI / 180.0;
	c = cos(a);
	s = sin(a);
	axis = vec_normalize(axis);
	dot = vec_dot(v, axis);
	cross = vec_cross(axis, v);
	v.x = v.x * c + cross.x * s + axis.x * dot * (1 - c);
	v.y = v.y * c + cross.y * s + axis.y * dot * (1 - c);
	v.z = v.z * c + cross.z * s + axis.z * dot * (1 - c);
	return (v);
}
