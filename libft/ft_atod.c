/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 00:41:55 by scraeyme          #+#    #+#             */
/*   Updated: 2025/07/12 15:26:34 by scraeyme         ###   ########.fr       */
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

double	ft_atod(const char *nptr)
{
	double	res;
	double	floating;
	char	**tab;

	if (!nptr)
		return (0);
	tab = ft_splitfirst((char *)nptr, '.');
	if (!tab)
		return (0);
	res = ft_atol(tab[0]);
	if (!is_floating(nptr) || (tab[1] && !ft_isdigit(tab[1][0])))
	{
		ft_tabfree(tab, ft_tablen(tab));
		return (res);
	}
	floating = ft_atol(tab[1]);
	if (res < 0 || ((size_t)ft_strcharindex((char *)nptr, '-')
			!= (size_t)(ft_strlen((char *)nptr) - 1)))
		res -= floating / ft_pow(10, ft_intlen((int)floating));
	else
		res += floating / ft_pow(10, ft_intlen((int)floating));
	ft_tabfree(tab, ft_tablen(tab));
	return (res);
}
