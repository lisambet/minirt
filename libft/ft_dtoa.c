/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:15:17 by scraeyme          #+#    #+#             */
/*   Updated: 2025/04/30 16:06:37 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

char	*ft_dtoa(double d)
{
	char	*str;
	char	*tmp;
	int		n;

	str = ft_itoa((int)d);
	if (!str)
		return (NULL);
	d -= (int)d;
	n = (int)round(d * 100);
	if (n < 0)
		n *= -1;
	str = ft_strjoin_free(str, ".");
	if (n > -10 && n != 0 && n < 10)
		str = ft_strjoin_free(str, "0");
	if (n != 0)
	{
		tmp = ft_itoa(n);
		str = ft_strjoin_free(str, tmp);
		free(tmp);
	}
	else
		str = ft_strjoin_free(str, "00");
	return (str);
}
