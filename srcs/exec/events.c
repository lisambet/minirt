/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:05:09 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/24 13:25:25 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec	rotate_vec(t_vec v, t_vec axis, double angle_deg)
{
	double	a;
	double	c;
	double	s;
	t_vec	cross;
	double	dot;

	a = angle_deg * PI / 180.0;
	c = cos(a);
	s = sin(a);
	axis = vec_normalize(axis);
	dot = vec_dot(v, axis);
	cross = vec_cross(axis, v);
	v.x = v.x * c + cross.x * s + axis.x * dot * (1 - c);
	v.y = v.y * c + cross.y * s + axis.y * dot * (1 - c);
	v.z = v.z * c + cross.z * s + axis.z * dot * (1 - c);
	return (v);
}

void	events_init(t_scene *s)
{
	mlx_hook(s->win, KeyPress, KeyPressMask, key_press, s);
	mlx_hook(s->win, DestroyNotify, StructureNotifyMask, close_window, s);
}

static void	move_camera(int keycode, t_scene *s, bool *moved)
{
	printf("%d", keycode);
	if (keycode == 1731)
		s->camera.pos = vec_add(s->camera.pos,
				vec_mul(s->camera.look_dir, MOVE_SPEED));
	else if (keycode == 1753)
		s->camera.pos = vec_sub(s->camera.pos,
				vec_mul(s->camera.look_dir, MOVE_SPEED));
	else if (keycode == 1734)
		s->camera.pos = vec_sub(s->camera.pos,
				vec_mul(s->camera.right_vec, MOVE_SPEED));
	else if (keycode == 1751)
		s->camera.pos = vec_add(s->camera.pos,
				vec_mul(s->camera.right_vec, MOVE_SPEED));
	else if (keycode == XK_space)
		s->camera.pos.y += MOVE_SPEED;
	else if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		s->camera.pos.y -= MOVE_SPEED;
	else
		return ;
	*moved = true;
}

static void	rotate_camera(int keycode, t_scene *s, bool *moved)
{
	if (keycode == XK_Left)
		s->camera.dir = rotate_vec(s->camera.dir, vec(0, 1, 0),
				ROTATION_ANGLE);
	else if (keycode == XK_Right)
		s->camera.dir = rotate_vec(s->camera.dir, vec(0, 1, 0),
				-ROTATION_ANGLE);
	else if (keycode == XK_Up)
		s->camera.dir = rotate_vec(s->camera.dir, s->camera.right_vec,
				ROTATION_ANGLE);
	else if (keycode == XK_Down)
		s->camera.dir = rotate_vec(s->camera.dir, s->camera.right_vec,
				-ROTATION_ANGLE);
	else
		return ;
	*moved = true;
}

int	key_press(int keycode, t_scene *s)
{
	bool	moved;

	moved = false;
	if (keycode == 65307)
		close_window(s);
	move_camera(keycode, s, &moved);
	rotate_camera(keycode, s, &moved);
	if (moved)
	{
		s->camera.dir = vec_normalize(s->camera.dir);
		recalculate_camera_basis(s);
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
