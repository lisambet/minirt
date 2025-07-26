/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:14:54 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/26 13:15:42 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select_after_light(t_scene *s)
{
	if (s->spheres)
	{
		s->selected_object_type = SEL_SPHERE;
		s->selected_object_ptr = s->spheres;
	}
	else if (s->planes)
	{
		s->selected_object_type = SEL_PLANE;
		s->selected_object_ptr = s->planes;
	}
	else if (s->cylinders)
	{
		s->selected_object_type = SEL_CYLINDER;
		s->selected_object_ptr = s->cylinders;
	}
	else
	{
		s->selected_object_type = SEL_CAMERA;
		s->selected_object_ptr = &s->camera;
	}
}

void	select_after_all_spheres(t_scene *s)
{
	if (s->planes)
	{
		s->selected_object_type = SEL_PLANE;
		s->selected_object_ptr = s->planes;
	}
	else if (s->cylinders)
	{
		s->selected_object_type = SEL_CYLINDER;
		s->selected_object_ptr = s->cylinders;
	}
	else
	{
		s->selected_object_type = SEL_CAMERA;
		s->selected_object_ptr = &s->camera;
	}
}

void	select_after_all_planes(t_scene *s)
{
	if (s->cylinders)
	{
		s->selected_object_type = SEL_CYLINDER;
		s->selected_object_ptr = s->cylinders;
	}
	else
	{
		s->selected_object_type = SEL_CAMERA;
		s->selected_object_ptr = &s->camera;
	}
}

void	select_after_all_cylinders(t_scene *s)
{
	s->selected_object_type = SEL_CAMERA;
	s->selected_object_ptr = &s->camera;
}


void	select_camera_to_light(t_scene *s)
{
	s->selected_object_type = SEL_LIGHT;
	s->selected_object_ptr = &s->light;
}