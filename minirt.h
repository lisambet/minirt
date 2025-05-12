/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:36 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/12 17:59:42 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
#include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#define WIDTH 800
#define HEIGHT 450



typedef struct s_vec
{
	double x;
	double y;
	double z;
} t_vec, t_point;

typedef t_vec t_color;
typedef t_vec t_point;


typedef struct s_camera
{
	t_point pos;
	t_vec dir;
	double	zoom;
	t_vec	look_dir;

} t_camera;

typedef struct s_amb
{
    float    i;
    t_color    color;
}    t_amb;

typedef struct s_lgt
{
    t_vec    vtx;
    float    i;
    t_color    color;
	struct s_lgt *next;
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

typedef struct s_plane
{
	t_vec    vtx;
    t_vec    rot;
	t_point p0;
	t_vec normal;
	t_color color;
	struct s_plane *next;
} t_plane;

typedef struct s_scene
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*data;
	t_vec	origin;
	t_vec	horizontal;
	t_vec	vertical;
	t_vec	lower_left_corner;
	t_camera camera;
	t_sphere *spheres;
	t_plane *planes;
	t_cylinder *cylinders;
	t_lgt *lights;
	t_amb *amb;
	int     should_exit;
}	t_scene;



typedef struct s_ray
{
	t_point orig;
	t_vec dir;
} t_ray;


t_scene	init_scene(void);
void	render(t_scene *s);

t_vec vec(double x, double y, double z);
t_vec vec_add(t_vec a, t_vec b);
t_vec vec_sub(t_vec a, t_vec b);
t_vec vec_mul(t_vec a, double t);
t_vec vec_div(t_vec a, double t);
t_vec vec_neg(t_vec v);
double vec_length(t_vec v);
t_vec vec_unit(t_vec v);
double vec_dot(t_vec a, t_vec b);
t_vec vec_normalize(t_vec v);

t_ray ray(t_point origin, t_vec direction);
t_point ray_at(t_ray r, double t);
t_color	ray_color(t_scene *s, t_ray r);
int get_color_int(t_color c);

void events_init(t_scene *s);
int key_press(int keycode, t_scene *s);
int close_window(t_scene *s);


t_sphere *sphere(t_point center, double radius, t_color color);
t_plane *plane(t_point p0, t_vec normal, t_color color);
t_cylinder *cylinder(t_point p0, t_vec normal, double radius, double height, t_color color);

bool hit_sphere(t_sphere *sphere, t_ray r, double *t_out);
bool hit_plane(t_plane *plane, t_ray r, double *t_out);
bool hit_cylinder(t_cylinder *cylinder, t_ray r, double *t_out);
bool hit_cap(t_ray r, t_point center, t_vec normal, double radius, double *t_out);

t_lgt *light(t_point vtx, float i, t_color color);
t_amb *amb(float i, t_color color);
t_color color_add(t_color a, t_color b, float intensity);

int			error_exit(char *msg);
int			cleanup_mlx(t_scene *s, char *msg);
int			cleanup_window(t_scene *s, char *msg);

# endif