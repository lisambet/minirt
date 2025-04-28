/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:05:09 by lisambet          #+#    #+#             */
/*   Updated: 2025/04/28 10:57:58 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h" ///SEGFAULT

void events_init(t_scene *s)
{
	printf("pointer 1%p\n", s->mlx);
	mlx_hook(s->win, KeyPress, KeyPressMask, key_press, s);
	mlx_hook(s->win, DestroyNotify, StructureNotifyMask, close_window, s);
	printf("pointer 2%p\n", s->mlx);
}

int key_press(int keycode, t_scene *s)
{
	if (keycode == 65307)
		exit(0);
		//close_window(s);
	render(s);
	return (0);
}
int close_window(t_scene *s)
{
	//usleep(10000);
	printf("pointer 3%p\n", s->mlx);
	mlx_destroy_image(s->mlx, s->img);
	mlx_destroy_window(s->mlx, s->win);
	mlx_destroy_display(s->mlx);
	free(s->mlx);
	exit(0);
}
