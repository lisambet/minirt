/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:26:44 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/12 03:20:13 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_cylinderadd_back(t_cylinder **head, t_cylinder *cylinder)
{
	t_cylinder	*tmp;

	tmp = *head;
	if (!*head)
		*head = cylinder;
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = cylinder;
	}
}

void	ft_cylinderclear(t_cylinder **cylinder)
{
	t_cylinder	*temp;

	if (!cylinder)
		return ;
	while (*cylinder)
	{
		temp = *cylinder;
		*cylinder = (*cylinder)->next;
		if (temp)
			free(temp);
	}
}

t_cylinder	*ft_cylindernew(t_point coords, t_point vector,
	double *values, t_color rgb)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->vtx = coords;
	cylinder->axis = vector;
	cylinder->radius = values[0];
	cylinder->height = values[1];
	cylinder->color = rgb;
	cylinder->next = NULL;
	return (cylinder);
}
