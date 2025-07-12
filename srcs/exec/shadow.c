/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:54:37 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/12 02:43:28 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_blocked_by_spheres(t_scene *s, t_ray shadow_ray, double t_max)
{
	double		current_t;
	t_sphere	*sphere;
	
	sphere = s->spheres;
	while (sphere)
	{
		if (hit_sphere(sphere, shadow_ray, &current_t))
		{
			if (current_t > SHADOW_BIAS && current_t < t_max)
				return (true); 
		}
		sphere = sphere->next;
	}
	return (false); 
}

bool	is_blocked_by_planes(t_scene *s, t_ray shadow_ray, double t_max)
{
	double	current_t;
	t_plane	*plane;
	
	plane = s->planes;
	while (plane)
	{
		if (hit_plane(plane, shadow_ray, &current_t))
		{
			if (current_t > SHADOW_BIAS && current_t < t_max)
				return (true); 
		}
		plane = plane->next;
	}
	return (false); 
}

bool	is_blocked_by_cylinders(t_scene *s, t_ray shadow_ray, double t_max)
{
	double		current_t;
	int			temp_hit_type; 
	t_cylinder	*cylinder;
	
	cylinder = s->cylinders;
	while (cylinder)
	{
		if (hit_cylinder(cylinder, shadow_ray, &current_t, &temp_hit_type))
		{
			if (current_t > SHADOW_BIAS && current_t < t_max)
				return (true); 
		}
		cylinder = cylinder->next;
	}
	return (false); 
}

bool	is_blocked(t_scene *s, t_ray shadow_ray, double t_max)
{
	if (is_blocked_by_spheres(s, shadow_ray, t_max))
		return (true);
	if (is_blocked_by_planes(s, shadow_ray, t_max))
		return (true);
	if (is_blocked_by_cylinders(s, shadow_ray, t_max))
		return (true);
	return (false);
}
