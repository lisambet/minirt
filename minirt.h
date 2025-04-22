/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:36 by lisambet          #+#    #+#             */
/*   Updated: 2025/04/21 15:15:41 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 450

typedef struct s_vec3
{
	double x;
	double y;
	double z;
} t_vec3;

typedef struct s_scene
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*data;
	t_vec3	origin;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	lower_left_corner;
}	t_scene;

typedef t_vec3 t_color;
typedef t_vec3 t_point3;

typedef struct s_ray
{
	t_point3 orig;
	t_vec3 dir;
} t_ray;

t_scene	init_scene(void);
void	render(t_scene *s);

t_vec3 vec3(double x, double y, double z);
t_vec3 vec3_add(t_vec3 a, t_vec3 b);
t_vec3 vec3_sub(t_vec3 a, t_vec3 b);
t_vec3 vec3_mul(t_vec3 a, double t);
t_vec3 vec3_div(t_vec3 a, double t);
double vec3_length(t_vec3 v);
t_vec3 vec3_unit(t_vec3 v);

t_ray ray(t_point3 origin, t_vec3 direction);
t_point3 ray_at(t_ray r, double t);
t_color ray_color(t_ray r);
int get_color_int(t_color c);

void events_init(t_scene *s);
int key_press(int keycode, t_scene *s);
int close_window(t_scene *s);