/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:31:35 by lisambet          #+#    #+#             */
/*   Updated: 2025/07/12 03:26:12 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_scene	scene;
	t_data data;

	if (ac < 2)
		return (ft_printerror("You need to specify an .rt file."));
	data = setup_data(av[1], ft_strlen(av[1]));
	if (data.error || !data.camera.enabled)
	{
		if (data.input)
			ft_tabfree(data.input, ft_tablen(data.input));
		return (free_structs(data));
	}
	init_scene(&scene);
	render(&scene);
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img, 0, 0);
	mlx_loop(scene.mlx);
	free_structs(data);
	ft_tabfree(data.input, ft_tablen(data.input));
	return (0);
}
