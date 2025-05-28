/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:36 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/28 18:17:38 by lisambet         ###   ########.fr       */
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

#define WIDTH 1600
#define HEIGHT 900
#define SHADOW_BIAS 0.001


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

typedef struct s_hit_record
{
	double  t;  
	t_point p;   
	t_color color;      
	void    *object_ptr; 
	int     object_type;
	int     hit;  
	int hit_type;       
} t_hit_record;

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
double vec_length_sq(t_vec v);
t_vec vec_unit(t_vec v);
double vec_dot(t_vec a, t_vec b);
t_vec vec_normalize(t_vec v);

double	get_m_projection(t_cylinder *cyl, t_ray r, double t);
void	get_cyl_eq_coefficients(t_cylinder *cyl, t_ray r, double *a, double *b, double *c);
bool	solve_quadratic(double a, double b, double c, double *t1, double *t2);

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
bool	hit_cylinder_side(t_cylinder *cyl, t_ray r, double *t_side);
bool	hit_cylinder_cap(t_cylinder *cyl, t_ray r, double *t_cap, double t_side);
bool hit_cylinder(t_cylinder *cyl, t_ray r, double *t_out, int *hit_type);

t_vec get_hit_object_normal(t_ray r, t_hit_record *rec);
t_vec get_cylinder_normal(t_cylinder *cyl, t_ray r, t_hit_record *rec);
t_color get_final_pixel_color(t_scene *s, t_ray r, t_hit_record *rec);
void    init_hit_record(t_hit_record *rec);

t_lgt *light(t_point vtx, float i, t_color color);
t_color light_objects(t_scene *s, t_ray r, void *object, int object_type, t_point intersection_point, double closest_t);
t_amb *amb(float i, t_color color);
t_color color_add(t_color c1, t_color c2);
double clamp(double value, double min, double max);
bool is_object_blocked(t_scene *s, t_ray shadow_ray, double t_max);

void check_cylinder_hits(t_scene *s, t_ray r, t_hit_record *rec);
void check_plane_hits(t_scene *s, t_ray r, t_hit_record *rec);
void check_sphere_hits(t_scene *s, t_ray r, t_hit_record *rec);

int			error_exit(char *msg);
int			cleanup_mlx(t_scene *s, char *msg);
int			cleanup_window(t_scene *s, char *msg);

# endif