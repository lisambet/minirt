/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:18:56 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/24 10:46:49 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_final_pixel_color(t_scene *s, t_ray r, t_hit_record *rec)
{
	t_vec	normal;
	t_color	object_color;
	t_color	ambient_lighting;
	t_color	direct_lighting;
	t_color	final_color;

	object_color = rec->color;
	normal = get_hit_object_normal(r, rec);
	ambient_lighting = calculate_ambient_color(s, object_color);
	direct_lighting = calculate_direct_color(s, object_color, normal, rec->p);
	final_color = color_add(ambient_lighting, direct_lighting);
	return (final_color);
}

int	get_color_int(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.999 * c.red);
	g = (int)(255.999 * c.green);
	b = (int)(255.999 * c.blue);
	return ((r << 16) | (g << 8) | b);
}

t_color	ray_color(t_scene *s, t_ray r)
{
	t_hit_record	rec;

	init_hit_record(&rec);
	check_sphere_hits(s, r, &rec);
	check_plane_hits(s, r, &rec);
	check_cylinder_hits(s, r, &rec);
	if (rec.hit)
		return (get_final_pixel_color(s, r, &rec));
	else
		return ((t_color){0, 0, 0});
}
