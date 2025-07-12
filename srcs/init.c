/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:46:11 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/02 19:50:39 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_scene_objects(t_scene *s)
{
	t_sphere	*my_sphere;
	t_sphere	*my_sphere2;
	t_plane		*my_plane;
	t_cylinder	*my_cylinder;
	t_lgt		*my_light;
	t_lgt		*my_light2;
	t_amb		*my_amb;

	s->spheres = NULL;
	s->planes = NULL;
	s->cylinders = NULL;
	s->lights = NULL;
	s->amb = NULL;
	my_plane = plane(vec(-1, -2, -2), vec(0, 1, 0), vec(0, 0, 225));
	s->planes = my_plane;
	my_sphere = sphere(vec(-2, -0.5, -2), 0.5, vec(255, 255, 255));
	my_sphere->next = NULL;
	my_sphere2 = sphere(vec(0.5, -0.5, -2), 0.5, vec(255, 255, 255));
	my_sphere2->next = NULL;
	my_sphere->next = my_sphere2;
	s->spheres = my_sphere;
	my_cylinder = cylinder(vec(-0.5, -0.5, -2), vec(0, 1, 0), 0.8, 1, vec(255, 255, 255));
	s->cylinders = my_cylinder;
	my_light = light(vec(2.0, 5.0, 1), 0.7, vec(0, 0, 255));
	my_light->next = NULL; 
	my_light2 = light(vec(-3.0, 4.0, 2), 0.7, vec(255, 0, 0));
	my_light2->next = NULL;
	my_light->next = my_light2; 
	s->lights = my_light;
	my_amb = amb(0.2, vec(255, 255, 255));
	s->amb = my_amb;
}


void	init_camera(t_scene *s)
{
	double	aspect_ratio;
	double	viewport_height;
	double	viewport_width;

	aspect_ratio = (double)WIDTH / HEIGHT;
	viewport_height = 3.0;
	viewport_width = viewport_height * aspect_ratio;
	s->camera.zoom = 1;
	s->origin = vec(0, 0, 0);
	s->horizontal = vec(viewport_width, 0, 0);
	s->vertical = vec(0, viewport_height, 0);
	s->lower_left_corner = vec_sub(vec_sub(vec_sub(s->origin,
				vec_div(s->horizontal, 2)), vec_div(s->vertical, 2)),
			vec(0, 0, s->camera.zoom));
}

void	init_scene(t_scene *s)
{
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	init_scene_objects(s);
	s->mlx = mlx_init();
	if (!s->mlx)
		exit(error_exit("Failed to initialize mlx"));
	s->win = mlx_new_window(s->mlx, WIDTH, HEIGHT, "minirt");
	if (!s->win)
		exit(cleanup_mlx(s, "Failed to create window"));
	s->img = mlx_new_image(s->mlx, WIDTH, HEIGHT);
	if (!s->img)
		exit(cleanup_window(s, "Failed to create image"));
	s->data = (int *)mlx_get_data_addr(s->img, &bits_per_pixel,
			&line_length, &endian);
	init_camera(s);
	events_init(s);
}

void    init_hit_record(t_hit_record *rec)
{
    rec->t = INFINITY;
    rec->object_ptr = NULL;
    rec->object_type = OBJ_NONE;
    rec->hit = 0;
	rec->hit_type = 0;
}

void	draw_blocks(t_scene *s, size_t x, size_t y, t_color color)
{
	size_t	tx;
	size_t	ty;

	ty = 0;
	while (ty < (size_t)SCALEDOWN && ty + y < (size_t)HEIGHT)
	{
		tx = 0;
		while (tx < (size_t)SCALEDOWN && tx + x < (size_t)WIDTH)
		{
			s->data[(y + ty) * WIDTH + (x + tx)] = get_color_int(color);
			tx++;
		}
		ty++;
	}
}

void render(t_scene *s)
{
	size_t x;
	size_t y;
	double u;
	double v;
	t_ray r;
	t_vec direction;
	t_color color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			u = (double)x / (WIDTH - 1);
			v = (double)(HEIGHT - 1 - y) / (HEIGHT - 1);
			direction = vec_sub(vec_add(vec_add(s->lower_left_corner,
												vec_mul(s->horizontal, u)),
										vec_mul(s->vertical, v)),
								s->origin);
			r = ray(s->origin, direction);
			color = ray_color(s,r);
			draw_blocks(s, x, y, color);
			x += SCALEDOWN;
		}
		y += SCALEDOWN;
	}
	printf("Done rendering image.\n");
}


