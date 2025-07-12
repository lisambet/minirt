/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:07:21 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/12 03:22:00 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void free_spheres(t_sphere *head)
{
	t_sphere *current;
	t_sphere *next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void free_planes(t_plane *head)
{
	t_plane *current;
	t_plane *next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void free_cylinders(t_cylinder *head)
{
	t_cylinder *current;
	t_cylinder *next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void free_lights(t_lgt *head)
{
	t_lgt *current;
	t_lgt *next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

int	free_structs(t_data data)
{
	if (data.sphere)
		ft_sphereclear(&data.sphere);
	if (data.plane)
		ft_planeclear(&data.plane);
	if (data.cylinder)
		ft_cylinderclear(&data.cylinder);
	return (1);
}
