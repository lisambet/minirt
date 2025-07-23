/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:48:25 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/23 15:28:27 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sphere(char *input, t_scene *scene)
{
	char		**tab;
	t_point		coords;
	t_color		rgb;
	t_sphere	*sphere;

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
	coords = (t_point){ft_atod(tab[1]), ft_atod(tab[2]), ft_atod(tab[3])};
	rgb = (t_color){ft_atoi(tab[5]), ft_atoi(tab[6]), ft_atoi(tab[7])};
	sphere = ft_spherenew(coords, ft_atod(tab[4]), rgb);
	ft_sphereadd_back(&scene->spheres, sphere);
	ft_tabfree(tab, ft_tablen(tab));
}

void	parse_plane(char *input, t_scene *scene)
{
	char	**tab;
	t_point	coords;
	t_vec	vector;
	t_color	rgb;
	t_plane	*plane;

	if (ft_stroccur(input, ',') != 6)
		return (set_error(scene));
	ft_strreplace(input, ',', ' ');
	tab = ft_split(input, ' ');
	if (!tab || ft_tablen(tab) != 10 || !input_atodable(tab))
	{
		if (tab)
			ft_tabfree(tab, ft_tablen(tab));
		return (set_error(scene));
	}
	coords = (t_point){ft_atod(tab[1]), ft_atod(tab[2]), ft_atod(tab[3])};
	vector = vec_normalize((t_vec){ft_atod(tab[4]), ft_atod(tab[5]),
			ft_atod(tab[6])});
	rgb = (t_color){ft_atoi(tab[7]), ft_atoi(tab[8]), ft_atoi(tab[9])};
	plane = ft_planenew(coords, vector, rgb);
	ft_planeadd_back(&scene->planes, plane);
	ft_tabfree(tab, ft_tablen(tab));
}

void	parse_cylinder(char *input, t_scene *scene)
{
	char		**tab;
	t_point		coords;
	t_color		rgb;
	t_vec		axis;
	t_cylinder	*cylinder;

	if (ft_stroccur(input, ',') != 6)
		return (set_error(scene));
	ft_strreplace(input, ',', ' ');
	tab = ft_split(input, ' ');
	if (!tab || ft_tablen(tab) != 12 || !input_atodable(tab))
	{
		if (tab)
			ft_tabfree(tab, ft_tablen(tab));
		return (set_error(scene));
	}
	coords = (t_point){ft_atod(tab[1]), ft_atod(tab[2]), ft_atod(tab[3])};
	axis = vec_normalize((t_vec){ft_atod(tab[4]), ft_atod(tab[5]),
			ft_atod(tab[6])});
	rgb = (t_color){ft_atoi(tab[9]), ft_atoi(tab[10]), ft_atoi(tab[11])};
	cylinder = ft_cylindernew(coords, axis, (double [2]){ft_atod(tab[7]),
			ft_atod(tab[8])}, rgb);
	ft_cylinderadd_back(&scene->cylinders, cylinder);
	ft_tabfree(tab, ft_tablen(tab));
}
