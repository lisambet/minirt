/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:05:09 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/02 19:43:31 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h" ///SEGFAULT

void events_init(t_scene *s)
{
	mlx_hook(s->win, KeyPress, KeyPressMask, key_press, s);
	mlx_hook(s->win, DestroyNotify, StructureNotifyMask, close_window, s);
}

int key_press(int keycode, t_scene *s)
{
	if (keycode == 65307)
	{
		close_window(s);
		exit(0);
	}
	render(s);
	return (0);
}
int close_window(t_scene *s)
{
    cleanup_scene_data(s);

    if (s->img)
        mlx_destroy_image(s->mlx, s->img);
    if (s->win)
        mlx_destroy_window(s->mlx, s->win);
    if (s->mlx)
    {
        mlx_destroy_display(s->mlx);
        free(s->mlx);
    }
    exit(0);
}
