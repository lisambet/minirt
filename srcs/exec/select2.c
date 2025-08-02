/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:14:54 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/27 12:37:55 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select_after_light(t_scene *s)
{
	if (s->spheres)
	{
		s->selected_object = SEL_SPHERE;
		s->sel_obj_ptr = s->spheres;
	}
	else if (s->planes)
	{
		s->selected_object = SEL_PLANE;
		s->sel_obj_ptr = s->planes;
	}
	else if (s->cylinders)
	{
		s->selected_object = SEL_CYLINDER;
		s->sel_obj_ptr = s->cylinders;
	}
	else
	{
		s->selected_object = SEL_CAMERA;
		s->sel_obj_ptr = &s->camera;
	}
}

void	select_after_all_spheres(t_scene *s)
{
	if (s->planes)
	{
		s->selected_object = SEL_PLANE;
		s->sel_obj_ptr = s->planes;
	}
	else if (s->cylinders)
	{
		s->selected_object = SEL_CYLINDER;
		s->sel_obj_ptr = s->cylinders;
	}
	else
	{
		s->selected_object = SEL_CAMERA;
		s->sel_obj_ptr = &s->camera;
	}
}

void	select_after_all_planes(t_scene *s)
{
	if (s->cylinders)
	{
		s->selected_object = SEL_CYLINDER;
		s->sel_obj_ptr = s->cylinders;
	}
	else
	{
		s->selected_object = SEL_CAMERA;
		s->sel_obj_ptr = &s->camera;
	}
}

void	select_after_all_cylinders(t_scene *s)
{
	s->selected_object = SEL_CAMERA;
	s->sel_obj_ptr = &s->camera;
}

void	select_camera_to_light(t_scene *s)
{
	s->selected_object = SEL_LIGHT;
	s->sel_obj_ptr = &s->light;
}
