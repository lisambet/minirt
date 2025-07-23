/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:31:44 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/23 15:19:29 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_lgt	light(t_point vtx, float i, t_color color)
{
	t_lgt	new;

	new.vtx = vtx;
	new.i = i;
	new.color = color;
	new.color.red /= 255;
	new.color.green /= 255;
	new.color.blue /= 255;
	return (new);
}

t_amb	amb(float i, t_color color)
{
	t_amb	new;

	new.i = i;
	new.color = color;
	new.color.red /= 255;
	new.color.green /= 255;
	new.color.blue /= 255;
	new.enabled = 1;
	return (new);
}

t_color	get_single_light(t_scene *s, t_lgt light, t_color object_color,
		t_vec normal, t_point intersection_point)
{
	t_vec	vec_to_light;
	t_vec	light_dir;
	double	dist_to_light;
	t_ray	shadow_ray;
	double	diffuse_factor;

	vec_to_light = vec_sub(light.vtx, intersection_point);
	light_dir = vec_normalize(vec_to_light);
	dist_to_light = vec_length(vec_to_light);
	shadow_ray.orig = vec_add(intersection_point, vec_mul(normal, SHADOW_BIAS));
	shadow_ray.dir = light_dir;
	if (is_blocked(s, shadow_ray, dist_to_light))
		return ((t_color){0, 0, 0});
	diffuse_factor = fmax(vec_dot(normal, light_dir), 0.0);
	return ((t_color){object_color.red * light.color.red * diffuse_factor
		* light.i, object_color.green * light.color.green * diffuse_factor
		* light.i, object_color.blue * light.color.blue * diffuse_factor
		* light.i});
}

t_color	calculate_direct_color(t_scene *s, t_color object_color, t_vec normal,
		t_point intersection_point)
{
	t_color	direct_lighting;

	direct_lighting = (t_color){0, 0, 0};
	direct_lighting = color_add(direct_lighting, get_single_light(s, s->light,
				object_color, normal, intersection_point));
	return (direct_lighting);
}

t_color	calculate_ambient_color(t_scene *s, t_color object_color)
{
	t_color	ambient_lighting;

	ambient_lighting = (t_color){0, 0, 0};
	if (s->amb.enabled)
	{
		ambient_lighting.red = object_color.red * s->amb.color.red * s->amb.i;
		ambient_lighting.green = object_color.green * s->amb.color.green
			* s->amb.i;
		ambient_lighting.blue = object_color.blue * s->amb.color.blue
			* s->amb.i;
	}
	return (ambient_lighting);
}
