/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:36:41 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/23 15:25:46 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

char	**list_to_tab(t_list *lst)
{
	int		i;
	char	**tab;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tab = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	tmp = lst;
	i = 0;
	while (tmp)
	{
		tab[i] = ft_strdup(tmp->str);
		if (tab[i][0] && tab[i][ft_strlen(tab[i]) - 1] == '\n')
			tab[i] = ft_strcrop(tab[i], 1);
		i++;
		tmp = tmp->next;
	}
	ft_lstclear(&lst);
	return (tab);
}

char	**file_to_tab(int fd)
{
	t_list	*lst;
	t_list	*new;
	char	*tmp;

	lst = NULL;
	tmp = NULL;
	while (!tmp || lst)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		else if (ft_strisspace(tmp) || ft_strstartswith(tmp, "#"))
		{
			free(tmp);
			tmp = NULL;
			continue ;
		}
		new = ft_lstnew(tmp);
		if (!lst)
			lst = new;
		else
			ft_lstadd_back(&lst, new);
	}
	return (list_to_tab(lst));
}

char	**get_input(int fd)
{
	char	**tab;

	tab = file_to_tab(fd);
	if (!tab)
		return (NULL);
	if (ft_taboccur(tab, 'A') > 1 || ft_taboccur(tab, 'C') > 1
		|| ft_taboccur(tab, 'L') > 1)
	{
		ft_tabfree(tab, ft_tablen(tab));
		return (NULL);
	}
	return (tab);
}

t_scene	error_scene(t_scene scene, char *str)
{
	ft_printerror(str);
	scene.error = 1;
	return (scene);
}

t_scene	setup_scene(char *file, int len)
{
	t_scene	scene;
	int		fd;

	prefill_scene(&scene);
	if (len < 3 || ft_strncmp(&file[len - 3], ".rt", 3))
		return (error_scene(scene, "File must end with .rt"));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_scene(scene, "Invalid file"));
	scene.input = get_input(fd);
	if (!scene.input)
		return (error_scene(scene, "File couldn't be parsed."));
	fill_scene(&scene);
	if (scene.error && scene.input)
	{
		ft_tabfree(scene.input, ft_tablen(scene.input));
		scene.input = NULL;
	}
	close(fd);
	return (scene);
}
