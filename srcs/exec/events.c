/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:05:09 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/27 12:31:06 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	events_init(t_scene *s)
{
	mlx_hook(s->win, KeyPress, KeyPressMask, key_press, s);
	mlx_hook(s->win, DestroyNotify, StructureNotifyMask, close_window, s);
}

int	key_press(int keycode, t_scene *s)
{
	bool	moved;

	moved = false;
	printf("Key pressed: %d\n", keycode);
	if (keycode == 65307)
		close_window(s);
	else if (keycode == XK_Tab)
	{
		select_next_object(s);
		moved = true;
	}
	else
		apply_transform_to_selected(s, keycode, &moved);
	if (moved)
	{
		recalculate_camera_basis(s, 0);
		render(s, 0, 0);
		mlx_put_image_to_window(s->mlx, s->win, s->img, 0, 0);
	}
	return (0);
}

int	close_window(t_scene *s)
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
