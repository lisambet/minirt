/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:21:36 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/12 03:33:05 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "mlx.h"
# include "libft.h"
# include "objects.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

# define WIDTH 1600
# define HEIGHT 900
# define SHADOW_BIAS 0.001
# define SCALEDOWN 20
// #define MOVE_SPEED 1.0
// #define ROTATION_ANGLE 10.0 

typedef struct s_hit_record
{
	double  t;  
	t_point p;   
	t_color color;      
	void    *object_ptr; 
	int     object_type;
	int     hit;  
	int hit_type;     
	t_vec   normal;  
} t_hit_record;

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

typedef struct s_data
{
	t_amb		ambient;
	t_camera	camera;
	t_lgt		light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	char		**input;
	int			error;
}				t_data;

void recalculate_camera_basis(t_scene *s);

void	init_scene(t_scene *s);
void	render(t_scene *s);

t_vec vec(double x, double y, double z);
t_vec vec_add(t_vec a, t_vec b);
t_vec vec_sub(t_vec a, t_vec b);
t_vec vec_mul(t_vec a, double t);
t_vec vec_div(t_vec a, double t);
t_vec vec_neg(t_vec v);
double vec_length(t_vec v);
double vec_length_sq(t_vec v);
double vec_dot(t_vec a, t_vec b);
t_vec vec_normalize(t_vec v);
t_vec vec_cross(t_vec a, t_vec b);
t_vec rotate_vector(t_vec v, t_vec axis, double angle_degrees);
double	get_m_projection(t_cylinder *cyl, t_ray r, double t);

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

void free_spheres(t_sphere *head);
void free_planes(t_plane *head);
void free_cylinders(t_cylinder *head);
void free_lights(t_lgt *head);
void cleanup_scene_data(t_scene *s);


t_sphere *sphere(t_point center, double radius, t_color color);
t_plane *plane(t_point p0, t_vec normal, t_color color);
t_cylinder *cylinder(t_point p0, t_vec normal, double radius, double height, t_color color);

bool hit_sphere(t_sphere *sphere, t_ray r, double *t_out);
bool hit_plane(t_plane *plane, t_ray r, double *t_out);
bool	hit_cylinder_side(t_cylinder *cyl, t_ray r, double *t_side);
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
bool is_blocked(t_scene *s, t_ray shadow_ray, double t_max);

void check_cylinder_hits(t_scene *s, t_ray r, t_hit_record *rec);
void check_plane_hits(t_scene *s, t_ray r, t_hit_record *rec);
void check_sphere_hits(t_scene *s, t_ray r, t_hit_record *rec);

int			error_exit(char *msg);
int			cleanup_mlx(t_scene *s, char *msg);
int			cleanup_window(t_scene *s, char *msg);

// Utils
t_sphere	*ft_spherenew(t_point coords, double diameter, t_color rgb);
void	ft_sphereadd_back(t_sphere **head, t_sphere *sphere);
void	ft_sphereclear(t_sphere **sphere);
void	ft_planeadd_back(t_plane **head, t_plane *plane);
void	ft_planeclear(t_plane **plane);
t_plane	*ft_planenew(t_point coords, t_point vector, t_color rgb);
void	ft_cylinderadd_back(t_cylinder **head, t_cylinder *cylinder);
void	ft_cylinderclear(t_cylinder **cylinder);
t_cylinder	*ft_cylindernew(t_point coords, t_point vector,
	double *values, t_color rgb);

int	ft_printerror(char *str);
void	set_error(t_data *data);
int	free_structs(t_data data);
void	prefill_data(t_data *data);

// Parsing
t_data			fill_data(t_data *data, int i);
t_data			setup_data(char *file, int len);
void			check_values(t_data *data);
int				input_atodable(char **tab);

// Parsing - Objects
void			parse_sphere(char *input, t_data *data);
void			parse_plane(char *input, t_data *data);
void			parse_cylinder(char *input, t_data *data);

// Parsing - Render
void			parse_ambient(char *input, t_data *data);
void			parse_camera(char *input, t_data *data);
void			parse_diffuse(char *input, t_data *data);

#endif
