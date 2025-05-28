/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:31:44 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/28 18:19:04 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_lgt *light(t_point vtx, float i, t_color color)
{
	t_lgt	*new;

	new = malloc(sizeof(t_lgt));
	if (!new)
		return (NULL);
	new->vtx = vtx;
	new->i = i;
	new->color.x = color.x / 255.0;
	new->color.y = color.y / 255.0;
	new->color.z = color.z / 255.0;
	new->next = NULL;
	return (new);
}
t_amb *amb(float i, t_color color)
{
	t_amb	*new;

	new = malloc(sizeof(t_amb));
	if (!new)
		return (NULL);
	new->i = i;
	new->color.x = color.x / 255.0;
	new->color.y = color.y / 255.0;
	new->color.z = color.z / 255.0;
	return (new);
}

t_color	calculate_direct_color(t_scene *s, t_color object_color,
			t_vec normal, t_point intersection_point)
{
	t_color	direct_lighting;
	t_lgt	*light;
	t_vec	light_dir;
	double	diffuse_factor;
	t_vec vec_to_light;
	t_ray   shadow_ray;
    double  dist_to_light;  

	direct_lighting = (t_color){0, 0, 0};
	light = s->lights;
	if (light)
	{
		vec_to_light = vec_sub(light->vtx, intersection_point);
		light_dir = vec_normalize(vec_sub(light->vtx, intersection_point));
		dist_to_light = vec_length(vec_to_light);
		shadow_ray.orig = vec_add(intersection_point, vec_mul(normal, SHADOW_BIAS));
        shadow_ray.dir = light_dir;
        if (is_object_blocked(s, shadow_ray, dist_to_light))
            return (direct_lighting);
		diffuse_factor = fmax(vec_dot(normal, light_dir), 0.0);
		direct_lighting.x = object_color.x
			* light->color.x * diffuse_factor * light->i;
		direct_lighting.y = object_color.y
			* light->color.y * diffuse_factor * light->i;
		direct_lighting.z = object_color.z
			* light->color.z * diffuse_factor * light->i;
	}
	return (direct_lighting);
}

t_color	calculate_ambient_color(t_scene *s, t_color object_color)
{
	t_color	ambient_lighting;

	ambient_lighting = (t_color){0, 0, 0};
	if (s->amb)
	{
		ambient_lighting.x = object_color.x
			* s->amb->color.x * s->amb->i;
		ambient_lighting.y = object_color.y
			* s->amb->color.y * s->amb->i;
		ambient_lighting.z = object_color.z
			* s->amb->color.z * s->amb->i;
	}
	return (ambient_lighting);
}


t_color get_final_pixel_color(t_scene *s, t_ray r, t_hit_record *rec)
{
    t_vec   normal;
    t_color object_color;
    t_color ambient_lighting;
    t_color direct_lighting;
    t_color final_color;

    object_color = rec->color;
    normal = get_hit_object_normal(r, rec);
    ambient_lighting = calculate_ambient_color(s, object_color);
    direct_lighting = calculate_direct_color(s, object_color, normal, rec->p);
    final_color = color_add(ambient_lighting, direct_lighting);

    return final_color;
}

int	get_color_int(t_color c)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255.999 * c.x);
	g = (int)(255.999 * c.y);
	b = (int)(255.999 * c.z);
	return ((r << 16) | (g << 8) | b);
}

t_color ray_color(t_scene *s, t_ray r)
{
    t_hit_record rec;

    init_hit_record(&rec);

    check_sphere_hits(s, r, &rec);
    check_plane_hits(s, r, &rec);
    check_cylinder_hits(s, r, &rec);

    if (rec.hit)
        return get_final_pixel_color(s, r, &rec);
    else
        return (t_color){0, 0, 0};

}
