/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:36 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/26 13:58:38 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "libft.h"
# include "mlx.h"
# include "objects.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1600
# define HEIGHT 900
# define SHADOW_BIAS 0.001
# define SCALEDOWN 5
# define PI 3.14159265358979323846
# define MOVE_SPEED 1
# define ROTATION_ANGLE 10.0

enum e_selected_object_type
{
	SEL_NONE = -1,
	SEL_CAMERA,
	SEL_LIGHT,
	SEL_SPHERE,
	SEL_PLANE,
	SEL_CYLINDER
};

typedef struct s_hit_record
{
	double		t;
	t_point		p;
	t_color		color;
	void		*object_ptr;
	int			object_type;
	int			hit;
	int			hit_type;
	t_vec		normal;
}				t_hit_record;

typedef struct s_scene
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*data;
	t_vec		origin;
	t_vec		horizontal;
	t_vec		vertical;
	t_vec		lower_left_corner;
	t_camera	camera;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	t_lgt		light;
	t_amb		amb;
	char		**input;
	int			error;
	int			should_exit;
enum			e_selected_object_type selected_object_type;
	void						*selected_object_ptr;
}				t_scene;

typedef struct s_ray
{
	t_point		orig;
	t_vec		dir;
}				t_ray;

void			recalculate_camera_basis(t_scene *s);

void			init_scene(t_scene *s);
void			render(t_scene *s, double u, double v);

t_vec			vec(double x, double y, double z);
t_vec			vec_add(t_vec a, t_vec b);
t_vec			vec_sub(t_vec a, t_vec b);
t_vec			vec_mul(t_vec a, double t);
t_vec			vec_div(t_vec a, double t);
t_vec			vec_neg(t_vec v);
double			vec_length(t_vec v);
double			vec_length_sq(t_vec v);
double			vec_dot(t_vec a, t_vec b);
t_vec			vec_normalize(t_vec v);
t_vec			vec_cross(t_vec a, t_vec b);
double			get_m_projection(t_cylinder *cyl, t_ray r, double t);

double			get_m_projection(t_cylinder *cyl, t_ray r, double t);
void			get_cyl_eq_coefficients(t_cylinder *cyl, t_ray r,
					double *indices[3]);
bool			solve_quadratic(double indices[3], double *t1,
					double *t2);

t_ray			ray(t_point origin, t_vec direction);
t_point			ray_at(t_ray r, double t);
t_color			ray_color(t_scene *s, t_ray r);
int				get_color_int(t_color c);

void			events_init(t_scene *s);
int				key_press(int keycode, t_scene *s);
int				close_window(t_scene *s);

t_vec	rotate_vec(t_vec v, t_vec axis, double angle_deg);
void	rotate_camera(t_scene *s, int keycode);
void	rotate_plane(t_scene *s, int keycode, t_vec right);
void	rotate_cylinder(t_scene *s, int keycode, t_vec right);
void	rotate_selected_object(t_scene *s, int keycode, t_vec right, bool *moved);

void	move_light(int keycode, t_scene *s, bool *moved);
void	move_camera(int keycode, t_scene *s, bool *moved);
void	move_cylinder(int keycode, t_scene *s, bool *moved);
void	move_plane(int keycode, t_scene *s, bool *moved);

void            select_next_object(t_scene *s);
void	select_next_cylinder(t_scene *s);
void	select_next_plane(t_scene *s);
void	select_next_sphere(t_scene *s);
void	select_default(t_scene *s);
void	resize_selected_object(t_scene *s, int keycode, bool *moved);
void	rotate_selected_object_horizontal(t_scene *s, int keycode, t_vec obj_up_vec, bool *moved);
void	move_selected_object_vertical(t_scene *s, bool up, bool *moved);
void	move_selected_object(t_scene *s, t_vec dir, bool *moved, int sign);
void	init_plane_cylinder_vectors(t_scene *s,	t_vec *obj_right_vec, t_vec *obj_up_vec);
void	*get_next_node(void *current_ptr, int current_type);
void	select_after_light(t_scene *s);
void	select_after_all_spheres(t_scene *s);
void	select_after_all_planes(t_scene *s);
void	select_after_all_cylinders(t_scene *s);
void	select_camera_to_light(t_scene *s);
void	print_selected_object(t_scene *s);
void    apply_transform_to_selected(t_scene *s, int keycode, bool *moved);


void			free_spheres(t_sphere *head);
void			free_planes(t_plane *head);
void			free_cylinders(t_cylinder *head);
void			free_lights(t_lgt *head);
void			cleanup_scene_data(t_scene *s);

bool			hit_sphere(t_sphere *sphere, t_ray r, double *t_out, double t);
bool			hit_plane(t_plane *plane, t_ray r, double *t_out);
bool			hit_cylinder_side(t_cylinder *cyl, t_ray r, double *t_side,
					double m);
bool			hit_cylinder(t_cylinder *cyl, t_ray r, double *t_out,
					int *hit_type);

t_vec			get_hit_object_normal(t_ray r, t_hit_record *rec);
t_vec			get_cylinder_normal(t_cylinder *cyl, t_ray r,
					t_hit_record *rec);
t_color			get_final_pixel_color(t_scene *s, t_ray r, t_hit_record *rec);
void			init_hit_record(t_hit_record *rec);

t_lgt			light(t_point vtx, float i, t_color color);
t_color			light_objects(t_scene *s, t_ray r, void *object,
					int object_type, t_point intersection_point,
					double closest_t);
t_amb			amb(float i, t_color color);
t_color			color_add(t_color c1, t_color c2);
double			clamp(double value, double min, double max);
bool			is_blocked(t_scene *s, t_ray shadow_ray, double t_max);
t_color			calculate_ambient_color(t_scene *s, t_color object_color);
t_color			calculate_direct_color(t_scene *s, t_color object_color,
					t_vec normal, t_point intersection_point);

void			check_cylinder_hits(t_scene *s, t_ray r, t_hit_record *rec);
void			check_plane_hits(t_scene *s, t_ray r, t_hit_record *rec);
void			check_sphere_hits(t_scene *s, t_ray r, t_hit_record *rec);

int				error_exit(char *msg);
int				cleanup_mlx(t_scene *s, char *msg);
int				cleanup_window(t_scene *s, char *msg);

// Utils
t_sphere		*ft_spherenew(t_point coords, double diameter, t_color rgb);
void			ft_sphereadd_back(t_sphere **head, t_sphere *sphere);
void			ft_sphereclear(t_sphere **sphere);
void			ft_planeadd_back(t_plane **head, t_plane *plane);
void			ft_planeclear(t_plane **plane);
t_plane			*ft_planenew(t_point coords, t_vec vector, t_color rgb);
void			ft_cylinderadd_back(t_cylinder **head, t_cylinder *cylinder);
void			ft_cylinderclear(t_cylinder **cylinder);
t_cylinder		*ft_cylindernew(t_point coords, t_vec vector, double *values,
					t_color rgb);
void			draw_blocks(t_scene *s, size_t x, size_t y, t_color color);

int				ft_printerror(char *str);
void			set_error(t_scene *scene);
int				free_structs(t_scene scene);
void			prefill_scene(t_scene *scene);

// Parsing
void			fill_scene(t_scene *scene);
t_scene			setup_scene(char *file, int len);
void			check_values(t_scene *scene);
int				input_atodable(char **tab);

// Parsing - Objects
void			parse_sphere(char *input, t_scene *scene);
void			parse_plane(char *input, t_scene *scene);
void			parse_cylinder(char *input, t_scene *scene);

// Parsing - Render
void			parse_ambient(char *input, t_scene *scene);
void			parse_camera(char *input, t_scene *scene);
void			parse_diffuse(char *input, t_scene *scene);

#endif
