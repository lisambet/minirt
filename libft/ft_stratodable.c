/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stratodable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:10:10 by scraeyme          #+#    #+#             */
/*   Updated: 2025/05/02 14:04:51 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_stratodable(char *str)
{
	int	point_count;
	int	i;

	i = 0;
	point_count = 0;
	while (ft_isspace(str[i]) || str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (point_count == 1 || i == 0 || !ft_isdigit(str[i - 1]))
				return (0);
			point_count++;
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
