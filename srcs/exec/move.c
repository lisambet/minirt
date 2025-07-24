/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:09:50 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/24 14:11:31 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	rotate_vec(t_vec v, t_vec axis, double angle_deg)
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

void	move_light(int keycode, t_scene *s, bool *moved)
{
	if (keycode == 1733)
		s->light.vtx = vec_add(s->light.vtx,
				vec_mul(s->camera.look_dir, MOVE_SPEED));
	else if (keycode == 1744)
		s->light.vtx = vec_sub(s->light.vtx,
				vec_mul(s->camera.look_dir, MOVE_SPEED));
	else if (keycode == 1729)
		s->light.vtx = vec_sub(s->light.vtx,
				vec_mul(s->camera.right_vec, MOVE_SPEED));
	else if (keycode == 1746)
		s->light.vtx = vec_add(s->light.vtx,
				vec_mul(s->camera.right_vec, MOVE_SPEED));
	else
		return ;
	*moved = true;
}

void	move_camera(int keycode, t_scene *s, bool *moved)
{
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

void	move_cylinder(int keycode, t_scene *s, bool *moved)
{
	t_cylinder	*c;

	c = s->cylinders;
	if (!c)
		return ;
	if (keycode == XK_I)
		c->vtx = vec_add(c->vtx,
				vec_mul(s->camera.look_dir, MOVE_SPEED));
	else if (keycode == XK_K)
		c->vtx = vec_sub(c->vtx,
				vec_mul(s->camera.look_dir, MOVE_SPEED));
	else if (keycode == XK_J)
		c->vtx = vec_sub(c->vtx,
				vec_mul(s->camera.right_vec, MOVE_SPEED));
	else if (keycode == XK_L)
		c->vtx = vec_add(c->vtx,
				vec_mul(s->camera.right_vec, MOVE_SPEED));
	else
		return ;
	*moved = true;
}

void	rotate_camera(int keycode, t_scene *s, bool *moved)
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