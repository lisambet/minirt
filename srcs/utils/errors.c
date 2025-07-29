/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 03:08:53 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/29 14:53:39 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline int	ratio_valid(float ratio)
{
	return (ratio >= 0.0f && ratio <= 1.0f);
}

inline int	vec_valid(t_point points)
{
	return ((points.x >= -1 && points.x <= 1) && (points.y >= -1
			&& points.y <= 1) && (points.z >= -1 && points.z <= 1)
		&& !(points.x == 0 && points.y == 0 && points.z == 0));
}

inline int	rgb_valid(t_color color)
{
	return ((color.red >= 0 && color.red <= 255
			&& (int)color.red == color.red)
		&& (color.green >= 0 && color.green <= 255
			&& (int)color.green == color.green)
		&& (color.blue >= 0 && color.blue <= 255
			&& (int)color.blue == color.blue));
}

inline void	set_error(t_scene *scene)
{
	scene->error = 1;
}

int	ft_printerror(char *str)
{
	ft_putendl_fd(RED "Error", 2);
	ft_putendl_fd(str, 2);
	ft_putstr_fd(NOC, 2);
	return (0);
}
