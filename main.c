#include "minirt.h"

int	main(void)
{
	t_scene	scene;

	init_scene(&scene);
	render(&scene);
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img, 0, 0);
	mlx_loop(scene.mlx);
	return (0);
}