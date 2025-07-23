/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:48:17 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/23 14:58:55 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(char *input, t_scene *scene)
{
	char	**tab;

	if (ft_stroccur(input, ',') != 2)
		return (set_error(scene));
	ft_strreplace(input, ',', ' ');
	tab = ft_split(input, ' ');
	if (!tab || ft_tablen(tab) != 5 || !input_atodable(tab))
	{
		if (tab)
			ft_tabfree(tab, ft_tablen(tab));
		return (set_error(scene));
	}
	scene->amb.i = ft_atof(tab[1]);
	scene->amb.color = (t_color){(double)(ft_atoi(tab[2])) / 255,
		(double)(ft_atoi(tab[3])) / 255, (double)(ft_atoi(tab[4])) / 255};
	scene->amb.enabled = 1;
	ft_tabfree(tab, ft_tablen(tab));
}

void	parse_camera(char *input, t_scene *scene)
{
	char	**tab;

	if (ft_stroccur(input, ',') != 4)
		return (set_error(scene));
	ft_strreplace(input, ',', ' ');
	tab = ft_split(input, ' ');
	if (!tab || ft_tablen(tab) != 8 || !input_atodable(tab))
	{
		if (tab)
			ft_tabfree(tab, ft_tablen(tab));
		return (set_error(scene));
	}
	scene->camera.pos = (t_point){ft_atod(tab[1]), ft_atod(tab[2]),
		ft_atod(tab[3])};
	scene->camera.dir = vec_normalize((t_point){ft_atod(tab[4]),
			ft_atod(tab[5]), ft_atod(tab[6])});
	scene->camera.fov = ft_atoi(tab[7]);
	scene->camera.enabled = 1;
	ft_tabfree(tab, ft_tablen(tab));
}

void	parse_diffuse(char *input, t_scene *scene)
{
	char	**tab;

	if (ft_stroccur(input, ',') != 4)
		return (set_error(scene));
	ft_strreplace(input, ',', ' ');
	tab = ft_split(input, ' ');
	if (!tab || ft_tablen(tab) != 8 || !input_atodable(tab))
	{
		if (tab)
			ft_tabfree(tab, ft_tablen(tab));
		return (set_error(scene));
	}
	scene->light.vtx = (t_vec){ft_atod(tab[1]), ft_atod(tab[2]),
		ft_atod(tab[3])};
	scene->light.i = ft_atof(tab[4]);
	scene->light.color = (t_color){(double)(ft_atoi(tab[5])),
		(double)(ft_atoi(tab[6])), (double)(ft_atoi(tab[7]))};
	scene->light.enabled = 1;
	ft_tabfree(tab, ft_tablen(tab));
}
