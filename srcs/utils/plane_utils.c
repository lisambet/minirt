/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:26:44 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/12 15:29:01 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_planeadd_back(t_plane **head, t_plane *plane)
{
	t_plane	*tmp;

	tmp = *head;
	if (!*head)
		*head = plane;
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = plane;
	}
}

void	ft_planeclear(t_plane **plane)
{
	t_plane	*temp;

	if (!plane)
		return ;
	while (*plane)
	{
		temp = *plane;
		*plane = (*plane)->next;
		if (temp)
			free(temp);
	}
}

t_plane	*ft_planenew(t_point coords, t_vec vector, t_color rgb)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->p0 = coords;
	plane->normal = vector;
	plane->color = rgb;
	plane->next = NULL;
	return (plane);
}
