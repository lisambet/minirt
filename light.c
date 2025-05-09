/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisambet <lisambet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:31:44 by lisambet          #+#    #+#             */
/*   Updated: 2025/05/08 19:33:55 by lisambet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_lgt *light(t_point vtx, float i, t_color color)
{
	t_lgt	*new;

	new = malloc(sizeof(t_lgt));
	if (!new)
		return (NULL);
	new->vtx = vtx;
	new->i = i;
	new->color = color;
	new->next = NULL;
	return (new);
}
t_amb *amb(float i, t_color color)
{
	t_amb	*new;

	new = malloc(sizeof(t_amb));
	if (!new)
		return (NULL);
	new->i = i;
	new->color = color;
	return (new);
}