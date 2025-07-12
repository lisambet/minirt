/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:31:50 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/12 03:15:10 by scraeyme         ###   ########.fr       */
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
		if (!vec_valid(cy->axis))
			return (0);
		cy = cy->next;
	}
	return (1);
}

void	check_values(t_data *data)
{
	t_plane		*tmp_pl;
	t_cylinder	*tmp_cy;

	if (!data->input)
	{
		data->error = 1;
		return ;
	}
	tmp_pl = data->plane;
	tmp_cy = data->cylinder;
	if ((data->ambient.enabled && !ratio_valid(data->ambient.i))
		|| (data->camera.enabled && (!vec_valid(data->camera.dir)
				|| data->camera.zoom > 180))
		|| (data->light.enabled && !ratio_valid(data->light.i))
		|| !objects_valid(tmp_pl, tmp_cy))
		data->error = 1;
}
