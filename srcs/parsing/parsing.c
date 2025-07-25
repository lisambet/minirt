/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:39:28 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/25 15:34:25 by scraeyme         ###   ########.fr       */
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

void	fill_objects(t_scene *scene, char *tmp)
{
	if (!ft_strncmp(tmp, "A ", 2))
		parse_ambient(tmp, scene);
	else if (!ft_strncmp(tmp, "C ", 2))
		parse_camera(tmp, scene);
	else if (!ft_strncmp(tmp, "L ", 2))
		parse_diffuse(tmp, scene);
	else if (!ft_strncmp(tmp, "sp ", 2))
		parse_sphere(tmp, scene);
	else if (!ft_strncmp(tmp, "pl ", 2))
		parse_plane(tmp, scene);
	else if (!ft_strncmp(tmp, "cy ", 2))
		parse_cylinder(tmp, scene);
	else
		scene->error = 1;
}

void	prefill_scene(t_scene *scene)
{
	scene->error = 0;
	scene->amb.enabled = 0;
	scene->amb.i = 0;
	scene->amb.color = (t_color){0, 0, 0};
	scene->light.i = 0;
	scene->light.color = (t_color){0, 0, 0};
	scene->light.vtx = (t_vec){0, 0, 0};
	scene->light.enabled = 0;
	scene->camera.enabled = 0;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	scene->input = NULL;
}

void	fill_scene(t_scene *scene)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_tabdup(scene->input, ft_tablen(scene->input));
	while (tmp && tmp[i] && !scene->error)
	{
		tmp[i] = ft_strtrim(tmp[i], ' ');
		tmp[i] = ft_strreplace(tmp[i], '\t', ' ');
		if (!tmp[i])
		{
			ft_tabfree(tmp, ft_tablen(scene->input));
			scene->error = 1;
			return ;
		}
		fill_objects(scene, tmp[i]);
		i++;
	}
	ft_tabfree(scene->input, ft_tablen(scene->input));
	scene->input = tmp;
	if (scene->camera.enabled)
		ft_tabfree(tmp, ft_tablen(tmp));
	check_values(scene);
	if (scene->error)
		ft_printerror("Objects are not valid.");
}
