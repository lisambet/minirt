/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:41:55 by scraeyme          #+#    #+#             */
/*   Updated: 2025/04/24 23:17:08 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_floating(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] && nptr[i] != '.')
	{
		while (nptr[i] && (nptr[i] == '+' || nptr[i] == '-'))
			i++;
		if (!ft_isdigit(nptr[i]))
			return (0);
		i++;
	}
	return (1);
}

float	ft_atof(const char *nptr)
{
	float	res;
	float	floating;
	char	**tab;

	if (!nptr)
		return (0);
	tab = ft_splitfirst((char *)nptr, '.');
	if (!tab)
		return (0);
	res = ft_atoi(tab[0]);
	if (!is_floating(nptr) || (tab[1] && !ft_isdigit(tab[1][0])))
	{
		ft_tabfree(tab, ft_tablen(tab));
		return (res);
	}
	floating = ft_atoi(tab[1]);
	res += floating / ft_pow(10, ft_intlen((int)floating));
	ft_tabfree(tab, ft_tablen(tab));
	return (res);
}
