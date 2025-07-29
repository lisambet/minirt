/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:31:50 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/29 14:54:54 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_cy(t_cylinder *cylinder)
{
	t_cylinder	*tmp_cy;

	tmp_cy = cylinder;
	while (tmp_cy)
	{
		if (!vec_valid(tmp_cy->normal) || !rgb_valid(tmp_cy->color)
			|| tmp_cy->height <= 0 || tmp_cy->diameter <= 0)
			return (0);
		tmp_cy->color = color_normalize(tmp_cy->color);
		tmp_cy = tmp_cy->next;
	}
	return (1);
}

static int	objects_valid(t_scene *scene)
{
	t_sphere	*tmp_sp;
	t_plane		*tmp_pl;

	tmp_sp = scene->spheres;
	tmp_pl = scene->planes;
	while (tmp_sp)
	{
		if (!rgb_valid(tmp_sp->color) || tmp_sp->diameter <= 0)
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
	return (check_cy(scene->cylinders) && rgb_valid(scene->light.color)
		&& rgb_valid(scene->amb.color));
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
