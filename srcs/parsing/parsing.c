/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:39:28 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/12 03:29:00 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	input_atodable(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!ft_stratodable(tab[i]) && i)
			return (0);
		i++;
	}
	return (1);
}

void	fill_objects(t_data *data, char *tmp)
{
	if (!ft_strncmp(tmp, "A ", 2))
		parse_ambient(tmp, data);
	else if (!ft_strncmp(tmp, "C ", 2))
		parse_camera(tmp, data);
	else if (!ft_strncmp(tmp, "L ", 2))
		parse_diffuse(tmp, data);
	else if (!ft_strncmp(tmp, "sp ", 2))
		parse_sphere(tmp, data);
	else if (!ft_strncmp(tmp, "pl ", 2))
		parse_plane(tmp, data);
	else if (!ft_strncmp(tmp, "cy ", 2))
		parse_cylinder(tmp, data);
	else
		data->error = 1;
}

void	prefill_data(t_data *data)
{
	data->error = 0;
	data->ambient.enabled = 0;
	data->ambient.i = 0;
	data->ambient.color = (t_color){0, 0, 0};
	data->light.i = 0;
	data->light.color = (t_color){0, 0, 0};
	data->light.vtx = (t_vec){0, 0, 0};
	data->light.enabled = 0;
	data->camera.enabled = 0;
	data->sphere = NULL;
	data->plane = NULL;
	data->cylinder = NULL;
	data->input = NULL;
}

t_data	fill_data(t_data *data, int i)
{
	char	**tmp;

	tmp = ft_tabdup(data->input, ft_tablen(data->input));
	while (tmp && tmp[i] && !data->error)
	{
		tmp[i] = ft_strtrim(tmp[i], ' ');
		tmp[i] = ft_strreplace(tmp[i], '\t', ' ');
		if (!tmp[i])
		{
			ft_tabfree(tmp, ft_tablen(data->input));
			data->error = 1;
			return (*data);
		}
		fill_objects(data, tmp[i]);
		i++;
	}
	ft_tabfree(data->input, ft_tablen(data->input));
	data->input = tmp;
	check_values(data);
	if (data->error)
		ft_printerror("Objects are not valid.");
	return (*data);
}
