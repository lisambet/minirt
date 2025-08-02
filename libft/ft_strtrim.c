/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:02:18 by scraeyme          #+#    #+#             */
/*   Updated: 2025/04/26 16:20:59 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char const *src, int start, int end)
{
	int	i;

	i = 0;
	while (start <= end)
	{
		dest[i] = src[start];
		start++;
		i++;
	}
	dest[i] = 0;
	free((char *)src);
	return (dest);
}

static char	*free_s1(char const *s1)
{
	free((char *)s1);
	return (NULL);
}

char	*ft_strtrim(char const *s1, char c)
{
	char	*str;
	int		start;
	int		end;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && s1[start] == c)
		start++;
	while (end && s1[end] == c)
		end--;
	if (start > end)
	{
		str = malloc(1);
		if (!str)
			return (free_s1((s1)));
		str[0] = 0;
		return (str);
	}
	str = malloc(end - start + 2);
	if (!str)
		return (free_s1(s1));
	str = ft_strcpy(str, s1, start, end);
	return (str);
}
