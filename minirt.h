/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:36 by lisambet          #+#    #+#             */
/*   Updated: 2025/04/26 13:13:24 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_camera
{
	t_point pos;
	t_vec dir;
	double	zoom;
	//t_vec	look_dir;

} t_camera;

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
}	t_scene;



typedef struct s_ray
{
	t_point orig;
	t_vec dir;
} t_ray;

typedef t_vec t_color;
typedef t_vec t_point;

t_scene	init_scene(void);
void	render(t_scene *s);

t_vec vec(double x, double y, double z);
t_vec vec_add(t_vec a, t_vec b);
t_vec vec_sub(t_vec a, t_vec b);
t_vec vec_mul(t_vec a, double t);
t_vec vec_div(t_vec a, double t);
double vec_length(t_vec v);
t_vec vec_unit(t_vec v);
double vec_dot(t_vec a, t_vec b);

t_ray ray(t_point origin, t_vec direction);
t_point ray_at(t_ray r, double t);
t_color ray_color(t_ray r);
int get_color_int(t_color c);

void events_init(t_scene *s);
int key_press(int keycode, t_scene *s);
int close_window(t_scene *s);

bool sphere(t_point center, double radius, t_ray r);
bool plane(t_point p0, t_vec normal, t_ray r);

//void update_camera(t_scene *s);