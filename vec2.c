/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:05:38 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/28 17:30:24 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


double vec_length(t_vec v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double vec_length_sq(t_vec v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec vec_unit(t_vec v)
{
	return vec_div(v, vec_length(v));
}

double vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec vec_neg(t_vec v)
{
	return vec(-v.x, -v.y, -v.z);
}

t_vec vec_normalize(t_vec v)
{
	double length;

	length = vec_length(v);
	if (length == 0)
		return vec(0, 0, 0);
	return vec_div(v, length);
}