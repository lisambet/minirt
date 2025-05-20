/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:31:44 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/20 14:46:10 by lisambet         ###   ########.fr       */
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

t_color get_final_pixel_color(t_scene *s, t_ray r, t_hit_record *rec)
{
    t_vec   normal;
    t_color object_color;
    t_color final_light_color = (t_color){0, 0, 0};
    t_lgt   *light = s->lights;

    object_color = rec->color;
    normal = get_hit_object_normal(r, rec);
    if (s->amb)
    {
		final_light_color.x = object_color.x * s->amb->color.x * s->amb->i;
        final_light_color.y = object_color.y * s->amb->color.y * s->amb->i;
        final_light_color.z = object_color.z * s->amb->color.z * s->amb->i;
    }
    if (light)
    {
        t_vec light_dir = vec_normalize(vec_sub(light->vtx, rec->p));
        double diffuse_factor = fmax(vec_dot(normal, light_dir), 0.0);

        t_color direct_contribution;
        direct_contribution.x = object_color.x * light->color.x * diffuse_factor * light->i;
        direct_contribution.y = object_color.y * light->color.y * diffuse_factor * light->i;
        direct_contribution.z = object_color.z * light->color.z * diffuse_factor * light->i;
        
        final_light_color = color_add(final_light_color, direct_contribution);
    }
    return final_light_color;
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
