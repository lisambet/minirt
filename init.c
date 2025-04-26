/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:46:11 by lisambet          #+#    #+#             */
/*   Updated: 2025/04/26 13:01:44 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	init_scene(void)
{
	t_scene	s;
	double	aspect_ratio;
	double	viewport_height;
	double	viewport_width;
	int bits_per_pixel;
int line_length;
int endian;

	s.mlx = mlx_init();
	if(!s.mlx)
	{
		perror("Failed to initialize mlx");
		exit(EXIT_FAILURE);
	}
	s.win = mlx_new_window(s.mlx, WIDTH, HEIGHT, "Gradient Sky");
	if(!s.win)
	{
		mlx_destroy_display(s.mlx);
		free(s.mlx);
		perror("Failed to create window");
		exit(EXIT_FAILURE);
	}
	s.img = mlx_new_image(s.mlx, WIDTH, HEIGHT);
	if(!s.img)
	{
		mlx_destroy_window(s.mlx, s.win);
		mlx_destroy_display(s.mlx);
		free(s.mlx);
		perror("Failed to create image");
		exit(EXIT_FAILURE);
	}
	s.data = (int *)mlx_get_data_addr(s.img, &bits_per_pixel, &line_length, &endian);
	aspect_ratio = (double)WIDTH / HEIGHT;
	viewport_height = 3.0;
	viewport_width = viewport_height * aspect_ratio;
	s.camera.zoom = 1;

	s.origin = vec(0, 0, 0);
	s.horizontal = vec(viewport_width, 0, 0);
	s.vertical = vec(0, viewport_height, 0);
	s.lower_left_corner = vec_sub(vec_sub(vec_sub(s.origin,
					vec_div(s.horizontal, 2)),
					vec_div(s.vertical, 2)),
					vec(0, 0, s.camera.zoom));
	events_init(&s);
	return (s);
}

void	render(t_scene *s)
{
	int		x;
	int		y;
	double	u;
	double	v;
	t_ray	r;
	t_vec	direction;
	t_color	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		printf("Rendering row %d\n", y);
		while (x < WIDTH)
		{
			u = (double)x / (WIDTH - 1);
			v = (double)(HEIGHT - 1 - y) / (HEIGHT - 1);
			direction = vec_sub(vec_add(vec_add(s->lower_left_corner,
							vec_mul(s->horizontal, u)),
							vec_mul(s->vertical, v)),
					s->origin);
			r = ray(s->origin, direction);
			color = ray_color(r);
			s->data[y * WIDTH + x] = get_color_int(color);
			x++;
		}
		y++;
	}
	printf("Done rendering image.\n");
}