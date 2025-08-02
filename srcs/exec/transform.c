/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 08:38:55 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/27 12:38:21 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*get_next_node(void *current_ptr, int current_type)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	if (!current_ptr)
		return (NULL);
	if (current_type == SEL_SPHERE)
	{
		sp = (t_sphere *)current_ptr;
		if (sp->next)
			return (sp->next);
	}
	if (current_type == SEL_PLANE)
	{
		pl = (t_plane *)current_ptr;
		if (pl->next)
			return (pl->next);
	}
	if (current_type == SEL_CYLINDER)
	{
		cy = (t_cylinder *)current_ptr;
		if (cy->next)
			return (cy->next);
	}
	return (NULL);
}

void	print_selected_object(t_scene *s)
{
	if (s->selected_object == SEL_CAMERA)
		printf("Selected object: Camera\n");
	else if (s->selected_object == SEL_LIGHT)
		printf("Selected object: Light\n");
	else if (s->selected_object == SEL_SPHERE)
		printf("Selected object: Sphere at (%.2f, %.2f, %.2f)\n",
			((t_sphere *)s->sel_obj_ptr)->center.x,
			((t_sphere *)s->sel_obj_ptr)->center.y,
			((t_sphere *)s->sel_obj_ptr)->center.z);
	else if (s->selected_object == SEL_PLANE)
		printf("Selected object: Plane at (%.2f, %.2f, %.2f)\n",
			((t_plane *)s->sel_obj_ptr)->p0.x,
			((t_plane *)s->sel_obj_ptr)->p0.y,
			((t_plane *)s->sel_obj_ptr)->p0.z);
	else if (s->selected_object == SEL_CYLINDER)
		printf("Selected object: Cylinder at (%.2f, %.2f, %.2f)\n",
			((t_cylinder *)s->sel_obj_ptr)->p0.x,
			((t_cylinder *)s->sel_obj_ptr)->p0.y,
			((t_cylinder *)s->sel_obj_ptr)->p0.z);
	else
		printf("Selected object: None\n");
}

void	init_plane_cylinder_vectors(t_scene *s, t_vec *obj_right_vec,
		t_vec *obj_up_vec)
{
	t_plane		*p;
	t_cylinder	*c;

	if (s->selected_object == SEL_PLANE)
	{
		p = (t_plane *)s->sel_obj_ptr;
		*obj_up_vec = vec_normalize(p->normal);
		*obj_right_vec = vec_normalize(vec_cross(*obj_up_vec, vec(0, 1, 0)));
		if (vec_length_sq(*obj_right_vec) < 1e-6)
			*obj_right_vec = vec_normalize(vec_cross(*obj_up_vec, vec(0, 0,
							1)));
	}
	else if (s->selected_object == SEL_CYLINDER)
	{
		c = (t_cylinder *)s->sel_obj_ptr;
		*obj_up_vec = vec_normalize(c->normal);
		*obj_right_vec = vec_normalize(vec_cross(*obj_up_vec, vec(0, 1, 0)));
		if (vec_length_sq(*obj_right_vec) < 1e-6)
			*obj_right_vec = vec_normalize(vec_cross(*obj_up_vec, vec(0, 0,
							1)));
	}
}
