/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:46:11 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/27 20:11:42 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_camera_basis(t_vec dir, t_vec *u, t_vec *v, t_vec *w)
{
	t_vec	up;

	dir = vec_normalize(dir);
	*w = vec_neg(dir);
	up = vec(0, 1, 0);
	if (fabs(vec_dot(dir, up)) > 0.9999)
		up = vec(0, 0, 1);
	*u = vec_normalize(vec_cross(up, *w));
	*v = vec_cross(*w, *u);
}

void	recalculate_camera_basis(t_scene *s, double ratio)
{
	t_vec	u;
	t_vec	v;
	t_vec	w;
	double	theta;
	double	h;

	ratio = (double)WIDTH / HEIGHT;
	theta = s->camera.fov * PI / 180.0;
	h = tan(theta / 2.0);
	get_camera_basis(s->camera.dir, &u, &v, &w);
	s->origin = s->camera.pos;
	s->horizontal = vec_mul(u, ratio * 2.0 * h);
	s->vertical = vec_mul(v, 2.0 * h);
	s->lower_left_corner = vec_sub(s->origin, vec_mul(w, 1.0));
	s->lower_left_corner = vec_sub(s->lower_left_corner, vec_div(s->horizontal,
				2.0));
	s->lower_left_corner = vec_sub(s->lower_left_corner, vec_div(s->vertical,
				2.0));
	s->camera.look_dir = s->camera.dir;
	s->camera.up_vec = v;
	s->camera.right_vec = u;
}

void	init_scene(t_scene *s)
{
	int	bits_per_pixel;
	int	line_length;
	int	endian;

	//s->camera.dir = vec(0, 0, 1);
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
	recalculate_camera_basis(s, 0);
	s->selected_object = SEL_CAMERA;
	s->sel_obj_ptr = &s->camera;
	printf("Selected object: Camera\n");
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
