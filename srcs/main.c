/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:31:35 by lisambet          #+#    #+#             */
/*   Updated: 2025/08/01 14:55:16 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_scene	scene;

	if (ac < 2)
		return (ft_printerror("You need to specify an .rt file."));
	scene = setup_scene(av[1], ft_strlen(av[1]));
	if (scene.error || !scene.camera.enabled)
	{
		if (scene.input && scene.camera.enabled)
			ft_tabfree(scene.input, ft_tablen(scene.input));
		return (free_structs(scene));
	}
	scene.scaledown = SCALEDOWN;
	init_scene(&scene);
	render(&scene, 0, 0);
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img, 0, 0);
	mlx_loop(scene.mlx);
	free_structs(scene);
	ft_tabfree(scene.input, ft_tablen(scene.input));
	return (0);
}
