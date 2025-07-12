/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:14:53 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/12 02:44:22 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vec_normalize(t_vec v)
{
	double	length;

	length = vec_length(v);
	if (length == 0)
		return vec(0, 0, 0);
	return vec_div(v, length);
}
