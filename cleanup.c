/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:37:09 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/02 12:46:59 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	error_exit(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	cleanup_window(t_scene *s, char *msg)
{
	mlx_destroy_window(s->mlx, s->win);
	mlx_destroy_display(s->mlx);
	free(s->mlx);
	return (error_exit(msg));
}

int	cleanup_mlx(t_scene *s, char *msg)
{
	mlx_destroy_display(s->mlx);
	free(s->mlx);
	return (error_exit(msg));
}

void cleanup_scene_data(t_scene *s)
{
    if (s->spheres)
        free_spheres(s->spheres);
    if (s->planes)
        free_planes(s->planes);
    if (s->cylinders)
        free_cylinders(s->cylinders);
    if (s->lights)
        free_lights(s->lights);
    if (s->amb)
        free(s->amb);
}

