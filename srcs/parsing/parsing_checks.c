/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:31:50 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/12 15:08:57 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline int	ratio_valid(float ratio)
{
	return (ratio >= 0.0f && ratio <= 1.0f);
}

static inline int	vec_valid(t_point points)
{
	return ((points.x >= -1 && points.x <= 1)
		&& (points.y >= -1 && points.y <= 1)
		&& (points.z >= -1 && points.z <= 1)
		&& !(points.x == 0 && points.y == 0 && points.z == 0));
}

static int	objects_valid(t_plane *pl, t_cylinder *cy)
{
	while (pl)
	{
		if (!vec_valid(pl->normal))
			return (0);
		pl = pl->next;
	}
	while (cy)
	{
		if (!vec_valid(cy->normal))
			return (0);
		cy = cy->next;
	}
	return (1);
}

void	check_values(t_scene *scene)
{
	t_plane		*tmp_pl;
	t_cylinder	*tmp_cy;

	if (!scene->input)
	{
		scene->error = 1;
		return ;
	}
	tmp_pl = scene->planes;
	tmp_cy = scene->cylinders;
	if ((scene->amb.enabled && !ratio_valid(scene->amb.i))
		|| (scene->camera.enabled && (!vec_valid(scene->camera.dir)
				|| scene->camera.fov > 180))
		|| (scene->light.enabled && !ratio_valid(scene->light.i))
		|| !objects_valid(tmp_pl, tmp_cy))
		scene->error = 1;
}
