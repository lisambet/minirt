/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:09:50 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/25 16:28:27 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	move_light(int keycode, t_scene *s, bool *moved)
{
	if (keycode == XK_t)
		s->light.vtx = vec_add(s->light.vtx,
				vec_mul(s->camera.look_dir, MOVE_SPEED));
	else if (keycode == XK_g)
		s->light.vtx = vec_sub(s->light.vtx,
				vec_mul(s->camera.look_dir, MOVE_SPEED));
	else if (keycode == XK_f)
		s->light.vtx = vec_sub(s->light.vtx,
				vec_mul(s->camera.right_vec, MOVE_SPEED));
	else if (keycode == XK_h)
		s->light.vtx = vec_add(s->light.vtx,
				vec_mul(s->camera.right_vec, MOVE_SPEED));
	else
		return ;
	*moved = true;
}

void	move_camera(int keycode, t_scene *s, bool *moved)
{
	//printf("%d\n", keycode);
	if (keycode == XK_w)
		s->camera.pos = vec_add(s->camera.pos,
				vec_mul(s->camera.look_dir, MOVE_SPEED));
	else if (keycode == XK_s)
		s->camera.pos = vec_sub(s->camera.pos,
				vec_mul(s->camera.look_dir, MOVE_SPEED));
	else if (keycode == XK_a)
		s->camera.pos = vec_sub(s->camera.pos,
				vec_mul(s->camera.right_vec, MOVE_SPEED));
	else if (keycode == XK_d)
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
	if (keycode == XK_i)
{	printf("%d\n", keycode);
		c->vtx = vec_add(c->p0,
				vec_mul(s->camera.dir, MOVE_SPEED));}
	else if (keycode == XK_k)
		c->vtx = vec_sub(c->p0,
				vec_mul(s->camera.dir, MOVE_SPEED));
	else if (keycode == XK_j)
		c->vtx = vec_sub(c->p0,
				vec_mul(s->camera.right_vec, MOVE_SPEED));
	else if (keycode == XK_l)
		c->vtx = vec_add(c->p0,
				vec_mul(s->camera.right_vec, MOVE_SPEED));
	else
		return ;
	*moved = true;
}

void	move_plane(int keycode, t_scene *s, bool *moved)
{
	t_plane	*p;

	p = s->planes;
	if (!p)
		return ;
	if (keycode == 55) // 7
		p->vtx = vec_add(p->vtx,
				vec_mul(s->camera.look_dir, MOVE_SPEED));
	else if (keycode == 57) // 9
		p->vtx = vec_sub(p->vtx,
				vec_mul(s->camera.look_dir, MOVE_SPEED));
	else if (keycode == 49) // 1
		p->vtx = vec_sub(p->vtx,
				vec_mul(s->camera.right_vec, MOVE_SPEED));
	else if (keycode == 51) // 3
		p->vtx = vec_add(p->vtx,
				vec_mul(s->camera.right_vec, MOVE_SPEED));
	else if (keycode == 52) // 4
		p->normal = rotate_vec(p->normal, vec(0, 1, 0), ROTATION_ANGLE);
	else if (keycode == 54) // 6
		p->normal = rotate_vec(p->normal, vec(0, 1, 0), -ROTATION_ANGLE);
	else if (keycode == 56) // 8
		p->normal = rotate_vec(p->normal,
				s->camera.right_vec, ROTATION_ANGLE);
	else if (keycode == 50) // 2
		p->normal = rotate_vec(p->normal,
				s->camera.right_vec, -ROTATION_ANGLE);
	else
		return ;
	p->normal = vec_normalize(p->normal);
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