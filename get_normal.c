/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:01:47 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/28 16:37:02 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double clamp(double value, double min, double max) 
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

t_color color_add(t_color c1, t_color c2)
{
    t_color result;

    result.x = c1.x + c2.x;
    result.y = c1.y + c2.y;
    result.z = c1.z + c2.z;
    result.x = clamp(result.x, 0.0, 1.0); //maybe put 0.1 in intensity as minimum 
    result.y = clamp(result.y, 0.0, 1.0);
    result.z = clamp(result.z, 0.0, 1.0);
    return result;
}

t_vec	get_hit_object_normal(t_ray r, t_hit_record *rec)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cyl;

	if (rec->object_type == OBJ_SPHERE)
	{
		sp = (t_sphere *)rec->object_ptr;
		return (vec_normalize(vec_sub(rec->p, sp->center)));
	}
	else if (rec->object_type == OBJ_PLANE)
	{
		pl = (t_plane *)rec->object_ptr;
		return (pl->normal);
	}
	else if (rec->object_type == OBJ_CYLINDER)
	{
		cyl = (t_cylinder *)rec->object_ptr;
		return (get_cylinder_normal(cyl, r, rec));
	}
	return ((t_vec){0, 0, 0});
}

t_vec	get_cylinder_normal(t_cylinder *cyl, t_ray r, t_hit_record *rec)
{
	t_vec	cap_normal;
	double	m;
	t_point	point_on_axis;
	t_vec	normalized_vec;

	if (rec->hit_type == 1)
	{
		cap_normal = cyl->normal;
		if (vec_dot(r.dir, cyl->normal) > 0)
			cap_normal = vec_neg(cap_normal);
		return (cap_normal);
	}
	m = vec_dot(vec_sub(rec->p, cyl->p0), cyl->normal);
	point_on_axis = vec_add(cyl->p0, vec_mul(cyl->normal, m));
	normalized_vec = vec_sub(rec->p, point_on_axis);
	return (vec_normalize(normalized_vec));
}
