/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:26:44 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/12 03:21:17 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_sphereadd_back(t_sphere **head, t_sphere *sphere)
{
	t_sphere	*tmp;

	tmp = *head;
	if (!*head)
		*head = sphere;
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = sphere;
	}
}

void	ft_sphereclear(t_sphere **sphere)
{
	t_sphere	*temp;

	if (!sphere)
		return ;
	while (*sphere)
	{
		temp = *sphere;
		*sphere = (*sphere)->next;
		if (temp)
			free(temp);
	}
}

t_sphere	*ft_spherenew(t_point coords, double diameter, t_color rgb)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = coords;
	sphere->radius = diameter;
	sphere->color = rgb;
	sphere->next = NULL;
	return (sphere);
}
