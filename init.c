/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:46:11 by lisambet          #+#    #+#             */
/*   Updated: 2025/04/21 15:10:18 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	init_scene(void)
{
	t_scene	s;
	double	aspect_ratio;
	double	viewport_height;
	double	viewport_width;
	double	focal_length;

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
	s.data = (int *)mlx_get_data_addr(s.img, &(int){0}, &(int){0}, &(int){0});

	aspect_ratio = (double)WIDTH / HEIGHT;
	viewport_height = 2.0;
	viewport_width = viewport_height * aspect_ratio;
	focal_length = 1.0;

	s.origin = vec3(0, 0, 0);
	s.horizontal = vec3(viewport_width, 0, 0);
	s.vertical = vec3(0, viewport_height, 0);
	s.lower_left_corner = vec3_sub(vec3_sub(vec3_sub(s.origin,
					vec3_div(s.horizontal, 2)),
					vec3_div(s.vertical, 2)),
					vec3(0, 0, focal_length));
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
	t_vec3	direction;
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
			direction = vec3_sub(vec3_add(vec3_add(s->lower_left_corner,
							vec3_mul(s->horizontal, u)),
							vec3_mul(s->vertical, v)),
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