/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:07:21 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/02 12:09:22 by lisambet         ###   ########.fr       */
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
