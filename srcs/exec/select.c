/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:09:10 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/27 12:37:44 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select_default(t_scene *s)
{
	s->selected_object = SEL_CAMERA;
	s->sel_obj_ptr = &s->camera;
}

void	select_next_sphere(t_scene *s)
{
	void	*next;

	next = get_next_node(s->sel_obj_ptr, SEL_SPHERE);
	if (next)
		s->sel_obj_ptr = next;
	else
		select_after_all_spheres(s);
}

void	select_next_plane(t_scene *s)
{
	void	*next;

	next = get_next_node(s->sel_obj_ptr, SEL_PLANE);
	if (next)
		s->sel_obj_ptr = next;
	else
		select_after_all_planes(s);
}

void	select_next_cylinder(t_scene *s)
{
	void	*next;

	next = get_next_node(s->sel_obj_ptr, SEL_CYLINDER);
	if (next)
		s->sel_obj_ptr = next;
	else
		select_after_all_cylinders(s);
}

void	select_next_object(t_scene *s)
{
	if (s->selected_object == SEL_CAMERA)
		select_camera_to_light(s);
	else if (s->selected_object == SEL_LIGHT)
		select_after_light(s);
	else if (s->selected_object == SEL_SPHERE)
		select_next_sphere(s);
	else if (s->selected_object == SEL_PLANE)
		select_next_plane(s);
	else if (s->selected_object == SEL_CYLINDER)
		select_next_cylinder(s);
	else
		select_default(s);
	print_selected_object(s);
}
