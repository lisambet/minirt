/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:09:50 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/26 14:05:55 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_selected_object(t_scene *s, t_vec dir, bool *moved,
	int sign)
{
	if (s->selected_object_type == SEL_CAMERA)
		s->camera.pos = vec_add(s->camera.pos, vec_mul(dir, MOVE_SPEED * sign));
	else if (s->selected_object_type == SEL_LIGHT)
		s->light.vtx = vec_add(s->light.vtx, vec_mul(dir, MOVE_SPEED * sign));
	else if (s->selected_object_type == SEL_SPHERE)
		((t_sphere *)s->selected_object_ptr)->center = vec_add(
			((t_sphere *)s->selected_object_ptr)->center, vec_mul(dir, MOVE_SPEED * sign));
	else if (s->selected_object_type == SEL_CYLINDER)
		((t_cylinder *)s->selected_object_ptr)->p0 = vec_add(
			((t_cylinder *)s->selected_object_ptr)->p0, vec_mul(dir, MOVE_SPEED * sign));
	*moved = true;
}
void	move_selected_object_vertical(t_scene *s, bool up, bool *moved)
{
	float	delta;

	if (up)
		delta = MOVE_SPEED;
	else
		delta = -MOVE_SPEED;
	if (s->selected_object_type == SEL_CAMERA)
		s->camera.pos.y += delta;
	else if (s->selected_object_type == SEL_LIGHT)
		s->light.vtx.y += delta;
	else if (s->selected_object_type == SEL_SPHERE)
		((t_sphere *)s->selected_object_ptr)->center.y += delta;
	else if (s->selected_object_type == SEL_PLANE)
		((t_plane *)s->selected_object_ptr)->p0.y += delta;
	else if (s->selected_object_type == SEL_CYLINDER)
		((t_cylinder *)s->selected_object_ptr)->p0.y += delta;
	*moved = true;
}


void	resize_selected_object(t_scene *s, int keycode, bool *moved)
{
	if (s->selected_object_type == SEL_SPHERE)
	{
		t_sphere	*sp;

		sp = (t_sphere *)s->selected_object_ptr;
		if (keycode == XK_KP_Add)
			sp->diameter += 1;
		else if (keycode == XK_KP_Subtract && sp->diameter > 0)
			sp->diameter -= 1;
		*moved = true;
	}
	else if (s->selected_object_type == SEL_CYLINDER)
	{
		t_cylinder	*c;

		c = (t_cylinder *)s->selected_object_ptr;
		if (keycode == XK_KP_Add)
			c->diameter += 1;
		else if (keycode == XK_KP_Subtract && c->diameter > 0)
			c->diameter -= 1;
		*moved = true;
	}
}

void	apply_transform_to_selected(t_scene *s, int keycode, bool *moved)
{
	t_vec	obj_right_vec;
	t_vec	obj_up_vec;

	init_plane_cylinder_vectors(s, &obj_right_vec, &obj_up_vec);
	if (keycode == XK_w)
		move_selected_object(s, s->camera.look_dir, moved, 1);
	else if (keycode == XK_s)
		move_selected_object(s, s->camera.look_dir, moved, -1);
	else if (keycode == XK_a)
		move_selected_object(s, s->camera.right_vec, moved, -1);
	else if (keycode == XK_d)
		move_selected_object(s, s->camera.right_vec, moved, 1);
	else if (keycode == XK_space)
		move_selected_object_vertical(s, true, moved);
	else if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		move_selected_object_vertical(s, false, moved);
	else if (keycode == XK_Left || keycode == XK_Right
		|| keycode == XK_Up || keycode == XK_Down)
		rotate_selected_object(s, keycode, obj_right_vec, moved);
	else if (keycode == XK_KP_Add || keycode == XK_KP_Subtract)
		resize_selected_object(s, keycode, moved);
}
