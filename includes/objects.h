/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 03:31:05 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/12 03:32:42 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct s_vec
{
	double x;
	double y;
	double z;
} t_vec, t_point;

typedef t_vec t_color;
typedef t_vec t_point;

enum e_object_type {
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_NONE = -1
};
typedef struct s_plane
{
	t_vec    vtx;
	t_vec    rot;
	t_point p0;
	t_vec normal;
	t_color color;
	struct s_plane *next;
} t_plane;

typedef struct s_camera
{
	t_point pos;
	t_vec	dir;
	double	zoom;
	t_vec	look_dir;
	t_vec   up_vec;
	bool	enabled;
} t_camera;

typedef struct s_amb
{
	float    i;
	t_color    color;
	bool	enabled;
}    t_amb;

typedef struct s_lgt
{
	t_vec    vtx;
	float    i;
	t_color    color;
	struct s_lgt *next;
	bool	enabled;
}    t_lgt;

typedef struct s_sphere
{
	t_vec    vtx;
	float    d;
	t_color    color;
	t_point center;
	double radius;
	struct s_sphere *next;
} t_sphere;

typedef struct s_cylinder
{
	t_vec    vtx;
	t_vec    rot;
	float    d;
	float    h;
	t_point p0;
	t_vec normal;
	t_color    color;
	t_point center;
	t_vec axis;
	double radius;
	double height;
	struct s_cylinder *next;
} t_cylinder;

#endif
