/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:27:45 by lisambet          #+#    #+#             */
/*   Updated: 2025/04/21 14:39:23 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3 vec3(double x, double y, double z)
{
	t_vec3 v = {x, y, z};
	return v;
}

t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{
	return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b)
{
	return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

t_vec3 vec3_mul(t_vec3 a, double t)
{
	return vec3(a.x * t, a.y * t, a.z * t);
}

t_vec3 vec3_div(t_vec3 a, double t)
{
	return vec3_mul(a, 1 / t);
}

double vec3_length(t_vec3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3 vec3_unit(t_vec3 v)
{
	return vec3_div(v, vec3_length(v));
}
