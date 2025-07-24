/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:14:53 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/24 10:24:45 by lisambet         ###   ########.fr       */
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
t_vec vec_cross(t_vec a, t_vec b)
{
    t_vec result;

    result.x = (a.y * b.z) - (a.z * b.y);
    result.y = (a.z * b.x) - (a.x * b.z);
    result.z = (a.x * b.y) - (a.y * b.x);

    return result;
}
