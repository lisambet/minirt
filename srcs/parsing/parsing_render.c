/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:48:17 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/12 03:16:37 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(char *input, t_data *data)
{
	char	**tab;

	if (ft_stroccur(input, ',') != 2)
		return (set_error(data));
	ft_strreplace(input, ',', ' ');
	tab = ft_split(input, ' ');
	if (!tab || ft_tablen(tab) != 5 || !input_atodable(tab))
	{
		if (tab)
			ft_tabfree(tab, ft_tablen(tab));
		return (set_error(data));
	}
	data->ambient.i = ft_atof(tab[1]);
	data->ambient.color = (t_color){ft_atoi(tab[2]),
		ft_atoi(tab[3]), ft_atoi(tab[4])};
	data->ambient.enabled = 1;
	ft_tabfree(tab, ft_tablen(tab));
}

void	parse_camera(char *input, t_data *data)
{
	char	**tab;

	if (ft_stroccur(input, ',') != 4)
		return (set_error(data));
	ft_strreplace(input, ',', ' ');
	tab = ft_split(input, ' ');
	if (!tab || ft_tablen(tab) != 8 || !input_atodable(tab))
	{
		if (tab)
			ft_tabfree(tab, ft_tablen(tab));
		return (set_error(data));
	}
	data->camera.pos = (t_point){ft_atod(tab[1]),
		ft_atod(tab[2]), ft_atod(tab[3])};
	data->camera.dir = vec_normalize((t_point){ft_atod(tab[4]),
			ft_atod(tab[5]), ft_atod(tab[6])});
	data->camera.zoom = ft_atoi(tab[7]);
	data->camera.enabled = 1;
	ft_tabfree(tab, ft_tablen(tab));
}

void	parse_diffuse(char *input, t_data *data)
{
	char	**tab;

	if (ft_stroccur(input, ',') != 4)
		return (set_error(data));
	ft_strreplace(input, ',', ' ');
	tab = ft_split(input, ' ');
	if (!tab || ft_tablen(tab) != 8 || !input_atodable(tab))
	{
		if (tab)
			ft_tabfree(tab, ft_tablen(tab));
		return (set_error(data));
	}
	data->light.vtx = (t_point){ft_atod(tab[1]),
		ft_atod(tab[2]), ft_atod(tab[3])};
	data->light.i = ft_atof(tab[4]);
	data->light.color = (t_color){ft_atoi(tab[5]),
		ft_atoi(tab[6]), ft_atoi(tab[7])};
	data->light.enabled = 1;
	ft_tabfree(tab, ft_tablen(tab));
}
