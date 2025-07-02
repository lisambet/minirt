/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:14:53 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/02 19:38:58 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_vec vec_cross(t_vec a, t_vec b)
// {
//     return vec(a.y * b.z - a.z * b.y,
//                a.z * b.x - a.x * b.z,
//                a.x * b.y - a.y * b.x);
// }

t_vec vec_normalize(t_vec v)
{
	double length;

	length = vec_length(v);
	if (length == 0)
		return vec(0, 0, 0);
	return vec_div(v, length);
}

// t_vec rotate_vector(t_vec v, t_vec axis, double angle_degrees)
// {
//     double angle_rad = angle_degrees * M_PI / 180.0;
//     double cos_theta = cos(angle_rad);
//     double sin_theta = sin(angle_rad);
//     t_vec rotated_v;

//     rotated_v = vec_add(vec_mul(v, cos_theta), vec_mul(vec_cross(axis, v), sin_theta));
//     rotated_v = vec_add(rotated_v, vec_mul(axis, vec_dot(axis, v) * (1 - cos_theta)));

//     return rotated_v;
// }