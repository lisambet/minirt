/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:07:21 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/23 14:28:11 by scraeyme         ###   ########.fr       */
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

int	free_structs(t_scene scene)
{
	if (scene.spheres)
		ft_sphereclear(&scene.spheres);
	if (scene.planes)
		ft_planeclear(&scene.planes);
	if (scene.cylinders)
		ft_cylinderclear(&scene.cylinders);
	return (1);
}
