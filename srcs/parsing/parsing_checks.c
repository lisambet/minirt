/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:31:50 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/29 14:34:50 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline int	ratio_valid(float ratio)
{
	return (ratio >= 0.0f && ratio <= 1.0f);
}

static inline int	vec_valid(t_point points)
{
	return ((points.x >= -1 && points.x <= 1) && (points.y >= -1
			&& points.y <= 1) && (points.z >= -1 && points.z <= 1)
		&& !(points.x == 0 && points.y == 0 && points.z == 0));
}

static inline int	rgb_valid(t_color color)
{
	return ((color.red >= 0 && color.red <= 255
			&& (int)color.red == color.red)
		&& (color.green >= 0 && color.green <= 255
			&& (int)color.green == color.green)
		&& (color.blue >= 0 && color.blue <= 255
			&& (int)color.blue == color.blue));
}

static int	objects_valid(t_scene *scene)
{
	t_sphere	*tmp_sp;
	t_plane		*tmp_pl;
	t_cylinder	*tmp_cy;

	tmp_sp = scene->spheres;
	tmp_pl = scene->planes;
	tmp_cy = scene->cylinders;
	while (tmp_sp)
	{
		if (!rgb_valid(tmp_sp->color))
			return (0);
		tmp_sp->color = color_normalize(tmp_sp->color);
		tmp_sp = tmp_sp->next;
	}
	while (tmp_pl)
	{
		if (!vec_valid(tmp_pl->normal) || !rgb_valid(tmp_pl->color))
			return (0);
		tmp_pl->color = color_normalize(tmp_pl->color);
		tmp_pl = tmp_pl->next;
	}
	while (tmp_cy)
	{
		if (!vec_valid(tmp_cy->normal) || !rgb_valid(tmp_cy->color))
			return (0);
		tmp_cy->color = color_normalize(tmp_cy->color);
		tmp_cy = tmp_cy->next;
	}
	return (rgb_valid(scene->light.color) && rgb_valid(scene->amb.color));
}

void	check_values(t_scene *scene)
{
	if (!scene->input)
	{
		scene->error = 1;
		return ;
	}
	if ((scene->amb.enabled && !ratio_valid(scene->amb.i))
		|| (scene->camera.enabled && (!vec_valid(scene->camera.dir)
				|| (scene->camera.fov < 0 || scene->camera.fov > 180)))
		|| (scene->light.enabled
			&& !ratio_valid(scene->light.i)) || !objects_valid(scene))
		scene->error = 1;
	if (!scene->error)
	{
		scene->light.color = color_normalize(scene->light.color);
		scene->amb.color = color_normalize(scene->amb.color);
	}
}
