/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:05:09 by lisambet          #+#    #+#             */
/*   Updated: 2025/04/26 13:17:01 by lisambet         ###   ########.fr       */
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
		exit(0);
		//close_window(s);
// else if (keycode == 119) // W
// {
//     t_vec move = vec_mul(s->camera.dir, 0.2); // скорость движения
//     s->origin = vec_add(s->origin, move);
//     s->lower_left_corner = vec_add(s->lower_left_corner, move);
// }
// else if (keycode == 115) // S
// {
//     t_vec move = vec_mul(s->camera.dir, 0.2);
//     s->origin = vec_sub(s->origin, move);
//     s->lower_left_corner = vec_sub(s->lower_left_corner, move);
// }
	
	render(s);
	return (0);
}
int close_window(t_scene *s)
{
	mlx_destroy_image(s->mlx, s->img);
	mlx_destroy_window(s->mlx, s->win);
	mlx_destroy_display(s->mlx);
	free(s->mlx);
	exit(0);
}
// void update_camera(t_scene *s)
// {
// 	double aspect_ratio = (double)WIDTH / HEIGHT;
// 	double viewport_height = 2.0 * s->camera.zoom;
// 	double viewport_width = viewport_height * aspect_ratio;
// 	double focal_length = 1.0;

// 	s->origin = vec(0, 0, 0);
// 	s->horizontal = vec(viewport_width, 0, 0);
// 	s->vertical = vec(0, viewport_height, 0);
// 	s->lower_left_corner = vec_sub(vec_sub(vec_sub(
// 		s->origin,
// 		vec_div(s->horizontal, 2)),
// 		vec_div(s->vertical, 2)),
// 		vec(0, 0, focal_length));
// }