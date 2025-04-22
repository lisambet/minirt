/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:27:45 by lisambet          #+#    #+#             */
/*   Updated: 2025/04/21 14:39:23 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vec(double x, double y, double z)
{
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec vec_add(t_vec a, t_vec b)
{
	return vec(a.x + b.x, a.y + b.y, a.z + b.z);
}

t_vec vec_sub(t_vec a, t_vec b)
{
	return vec(a.x - b.x, a.y - b.y, a.z - b.z);
}

t_vec vec_mul(t_vec a, double t)
{
	return vec(a.x * t, a.y * t, a.z * t);
}

t_vec vec_div(t_vec a, double t)
{
	return vec_mul(a, 1 / t);
}

double vec_length(t_vec v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec vec_unit(t_vec v)
{
	return vec_div(v, vec_length(v));
}

double vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}