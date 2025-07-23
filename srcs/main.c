/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:31:35 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/23 15:44:06 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_objects(t_scene scene)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	int			i;

	if (scene.amb.enabled)
	{
		printf("\n\033[36m--------------------	AMBIENT		--------------------\n");
		printf("Ratio:		%f\n", scene.amb.i);
		printf("RGB:		%f, %f, %f\n\n\033[0m", scene.amb.color.red,
					scene.amb.color.green, scene.amb.color.blue);
	}
	if (scene.camera.enabled)
	{
		printf("\033[34m--------------------	CAMERA		--------------------\n");
		printf("XYZ:		%f, %f, %f\n", scene.camera.pos.x,
					scene.camera.pos.y, scene.camera.pos.z);
		printf("Vector:		%f, %f, %f\n", scene.camera.dir.x,
					scene.camera.dir.y, scene.camera.dir.z);
		printf("FOV:		%f\n\n\033[0m", scene.camera.fov);
	}
	if (scene.light.enabled)
	{
		printf("\033[35m--------------------	LIGHT		--------------------\n");
		printf("XYZ:		%f, %f, %f\n", scene.light.vtx.x, scene.light.vtx.y,
					scene.light.vtx.z);
		printf("Ratio:		%f\n", scene.light.i);
		printf("RGB:		%f, %f, %f\n\n\033[0m", scene.light.color.red,
					scene.light.color.green, scene.light.color.blue);
	}
	i = 1;
	if (scene.spheres)
	{
		sphere = scene.spheres;
		printf("\033[33m--------------------	SPHERES		--------------------\n");
		while (sphere)
		{
			printf("\033[33m-- sphere #%d --\n", i);
			printf("XYZ:		%f, %f, %f\n", sphere->center.x,
						sphere->center.y, sphere->center.z);
			printf("Diameter:	%f\n", sphere->diameter);
			printf("RGB:		%f, %f, %f\n\n\033[0m", sphere->color.red,
						sphere->color.green, sphere->color.blue);
			sphere = sphere->next;
			i++;
		}
	}
	i = 1;
	if (scene.planes)
	{
		plane = scene.planes;
		printf("\033[32m--------------------	PLANES		--------------------\n");
		while (plane)
		{
			printf("\033[32m-- plane #%d --\n", i);
			printf("XYZ:		%f, %f, %f\n", plane->p0.x, plane->p0.y,
						plane->p0.z);
			printf("Vector:		%f, %f, %f\n", plane->normal.x, plane->normal.y,
						plane->normal.z);
			printf("RGB:		%f, %f, %f\n\n\033[0m", plane->color.red,
						plane->color.green, plane->color.blue);
			plane = plane->next;
			i++;
		}
	}
	i = 1;
	if (scene.cylinders)
	{
		cylinder = scene.cylinders;
		printf("\033[31m--------------------	CYLINDERS	--------------------\n");
		while (cylinder)
		{
			printf("\033[31m-- cylinder #%d --\n", i);
			printf("XYZ:		%f, %f, %f\n", cylinder->p0.x, cylinder->p0.y,
						cylinder->p0.z);
			printf("Axis:		%f, %f, %f\n", cylinder->normal.x,
						cylinder->normal.y, cylinder->normal.z);
			printf("Diameter:	%f\n", cylinder->diameter);
			printf("Height:		%f\n", cylinder->height);
			printf("RGB:		%f, %f, %f\n\n\033[0m", cylinder->color.red,
						cylinder->color.green, cylinder->color.blue);
			cylinder = cylinder->next;
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	t_scene	scene;

	if (ac < 2)
		return (ft_printerror("You need to specify an .rt file."));
	scene = setup_scene(av[1], ft_strlen(av[1]));
	if (scene.error || !scene.camera.enabled)
	{
		if (scene.input)
			ft_tabfree(scene.input, ft_tablen(scene.input));
		return (free_structs(scene));
	}
	// init_scene(&scene);
	print_objects(scene);
	render(&scene, 0, 0);
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img, 0, 0);
	mlx_loop(scene.mlx);
	free_structs(scene);
	ft_tabfree(scene.input, ft_tablen(scene.input));
	return (0);
}
