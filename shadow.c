/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:04:11 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/28 18:22:04 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool is_object_blocked(t_scene *s, t_ray shadow_ray, double t_max)
{
    double current_t;

    t_sphere *sphere = s->spheres;
    while (sphere)
    {
        if (hit_sphere(sphere, shadow_ray, &current_t))
        {
            if (current_t > SHADOW_BIAS && current_t < t_max)
                return (true);
        }
        sphere = sphere->next;
    }
    t_plane *plane = s->planes;
    while (plane)
    {
        if (hit_plane(plane, shadow_ray, &current_t))
        {
            if (current_t > SHADOW_BIAS && current_t < t_max)
                return (true);
        }
        plane = plane->next;
    }
    t_cylinder *cylinder = s->cylinders;
    int temp_hit_type;
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