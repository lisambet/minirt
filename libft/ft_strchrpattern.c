/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrpattern.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csenelle <csenelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:30:39 by csenelle          #+#    #+#             */
/*   Updated: 2025/03/06 16:11:52 by csenelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchrpattern(char *str, char *pattern)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == pattern[0] && (i == 0 || str[i - 1] == ' '))
		{
			while (str[i] == pattern[j] && str[i] && pattern[j])
			{
				i++;
				j++;
			}
			if (pattern[j] == '\0' && (str[i] == '\0' || ft_isspace(str[i])))
				return (1);
			j = 0;
		}
		if (str[i])
			i++;
	}
	return (0);
}

int	ft_strchrpatternfirstarg(char *str, char *pattern)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == pattern[0])
		{
			while (str[i] == pattern[j] && str[i] && pattern[j])
			{
				i++;
				j++;
			}
			if (pattern[j] == '\0')
				return (1);
			j = 0;
		}
		if (str[i])
			i++;
	}
	return (0);
}
