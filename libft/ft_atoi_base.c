/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenelle <csenelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:05:27 by csenelle          #+#    #+#             */
/*   Updated: 2024/12/10 13:15:31 by csenelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_index(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

unsigned int	ft_atoi_base(const char *nptr, char *base)
{
	int			base_len;
	int			index;
	long long	result;

	result = 0;
	while (ft_isspace(*nptr))
		nptr++;
	base_len = ft_strlen(base);
	if (*nptr == '0' && *(nptr + 1) == 'x')
		nptr += 2;
	index = get_index((char) *nptr, base);
	while (index != -1)
	{
		result = result * base_len + index;
		nptr++;
		index = get_index((char) *nptr, base);
	}
	return ((unsigned int) result);
}
