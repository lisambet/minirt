/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 03:08:53 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/12 14:20:55 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline void	set_error(t_scene *scene)
{
	scene->error = 1;
}

int	ft_printerror(char *str)
{
	ft_putendl_fd(RED "Error", 2);
	ft_putendl_fd(str, 2);
	ft_putstr_fd(NOC, 2);
	return (0);
}
