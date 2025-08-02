/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:37:03 by scraeyme          #+#    #+#             */
/*   Updated: 2025/04/26 16:10:56 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabfree(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (!tab[i])
		{
			i++;
			continue ;
		}
		free(tab[i]);
		tab[i] = 0;
		i++;
	}
	free(tab);
	tab = NULL;
}
