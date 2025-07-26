/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:48:09 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/26 13:58:34 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rotate_camera(t_scene *s, int keycode)
{
	if (keycode == XK_Left)
		s->camera.dir = rotate_vec(s->camera.dir,
				s->camera.up_vec, ROTATION_ANGLE);
	else if (keycode == XK_Right)
		s->camera.dir = rotate_vec(s->camera.dir,
				s->camera.up_vec, -ROTATION_ANGLE);
	else if (keycode == XK_Up)
		s->camera.dir = rotate_vec(s->camera.dir,
				s->camera.right_vec, ROTATION_ANGLE);
	else if (keycode == XK_Down)
		s->camera.dir = rotate_vec(s->camera.dir,
				s->camera.right_vec, -ROTATION_ANGLE);
}

void	rotate_plane(t_scene *s, int keycode, t_vec right)
{
	t_plane	*p;

	p = (t_plane *)s->selected_object_ptr;
	if (keycode == XK_Left)
		p->normal = rotate_vec(p->normal, vec(0, 0, 1), ROTATION_ANGLE);
	else if (keycode == XK_Right)
		p->normal = rotate_vec(p->normal, vec(0, 0, 1), -ROTATION_ANGLE);
	else if (keycode == XK_Up)
		p->normal = rotate_vec(p->normal, right, ROTATION_ANGLE);
	else if (keycode == XK_Down)
		p->normal = rotate_vec(p->normal, right, -ROTATION_ANGLE);
	p->normal = vec_normalize(p->normal);
}

void	rotate_cylinder(t_scene *s, int keycode, t_vec right)
{
	t_cylinder	*c;

	c = (t_cylinder *)s->selected_object_ptr;
	if (keycode == XK_Left)
		c->normal = rotate_vec(c->normal, vec(0, 1, 0), ROTATION_ANGLE);
	else if (keycode == XK_Right)
		c->normal = rotate_vec(c->normal, vec(0, 1, 0), -ROTATION_ANGLE);
	else if (keycode == XK_Up)
		c->normal = rotate_vec(c->normal, right, ROTATION_ANGLE);
	else if (keycode == XK_Down)
		c->normal = rotate_vec(c->normal, right, -ROTATION_ANGLE);
	c->normal = vec_normalize(c->normal);
}

void	rotate_selected_object(t_scene *s,
			int keycode, t_vec right, bool *moved)
{
	if (s->selected_object_type == SEL_CAMERA)
		rotate_camera(s, keycode);
	else if (s->selected_object_type == SEL_PLANE)
		rotate_plane(s, keycode, right);
	else if (s->selected_object_type == SEL_CYLINDER)
		rotate_cylinder(s, keycode, right);
	*moved = true;
}
