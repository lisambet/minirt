/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:46:11 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/23 15:43:50 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_camera(t_scene *s)
{
	double	aspect_ratio;
	double	viewport_height;
	double	viewport_width;

	aspect_ratio = (double)WIDTH / HEIGHT;
	viewport_height = 3.0;
	viewport_width = viewport_height * aspect_ratio;
	s->camera.fov = 1;
	s->origin = vec(0, 0, 0);
	s->horizontal = vec(viewport_width, 0, 0);
	s->vertical = vec(0, viewport_height, 0);
	s->lower_left_corner = vec_sub(vec_sub(vec_sub(s->origin,
					vec_div(s->horizontal, 2)), vec_div(s->vertical, 2)), vec(0,
				0, s->camera.fov));
}

void	init_scene(t_scene *s)
{
	int	bits_per_pixel;
	int	line_length;
	int	endian;

	s->mlx = mlx_init();
	if (!s->mlx)
		exit(error_exit("Failed to initialize mlx"));
	s->win = mlx_new_window(s->mlx, WIDTH, HEIGHT, "minirt");
	if (!s->win)
		exit(cleanup_mlx(s, "Failed to create window"));
	s->img = mlx_new_image(s->mlx, WIDTH, HEIGHT);
	if (!s->img)
		exit(cleanup_window(s, "Failed to create image"));
	s->data = (int *)mlx_get_data_addr(s->img, &bits_per_pixel, &line_length,
			&endian);
	init_camera(s);
	events_init(s);
}

void	init_hit_record(t_hit_record *rec)
{
	rec->t = INFINITY;
	rec->object_ptr = NULL;
	rec->object_type = OBJ_NONE;
	rec->hit = 0;
	rec->hit_type = 0;
}

void	render(t_scene *s, double u, double v)
{
	size_t	x;
	size_t	y;
	t_ray	r;
	t_vec	direction;
	t_color	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			u = (double)x / (WIDTH - 1);
			v = (double)(HEIGHT - 1 - y) / (HEIGHT - 1);
			direction = vec_sub(vec_add(vec_add(s->lower_left_corner,
							vec_mul(s->horizontal, u)), vec_mul(s->vertical,
							v)), s->origin);
			r = ray(s->origin, direction);
			color = ray_color(s, r);
			draw_blocks(s, x, y, color);
			x += SCALEDOWN;
		}
		y += SCALEDOWN;
	}
	printf("Done rendering image.\n");
}
