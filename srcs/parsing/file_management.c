/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:36:41 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/12 03:07:25 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_data	error_data(t_data data, char *str)
{
	ft_printerror(str);
	data.error = 1;
	return (data);
}

t_data	setup_data(char *file, int len)
{
	t_data	data;
	int		fd;

	prefill_data(&data);
	if (len < 3 || ft_strncmp(&file[len - 3], ".rt", 3))
		return (error_data(data, "File has invalid format, must end with .rt"));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_data(data, "Invalid file"));
	data.input = get_input(fd);
	if (!data.input)
		return (error_data(data, "File couldn't be parsed."));
	data = fill_data(&data, 0);
	if (data.error && data.input)
	{
		ft_tabfree(data.input, ft_tablen(data.input));
		data.input = NULL;
	}
	close(fd);
	return (data);
}
