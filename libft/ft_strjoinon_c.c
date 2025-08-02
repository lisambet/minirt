/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinon_c.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvillat <huvillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:42:04 by csenelle          #+#    #+#             */
/*   Updated: 2025/01/08 14:37:20 by huvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_2dvalues(char **av, int ac)
{
	int	i;
	int	j;
	int	count;

	i = 1;
	count = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] != ' ' && !ft_isdigit(av[i][j]) && av[i][j] != '-')
			{
				write(2, "Error\n", 6);
				exit(1);
			}
			count++;
			j++;
		}
		i++;
	}
	return (count);
}

char	*ft_strjoinon_c(int ac, char **av, int c)
{
	int			i;
	int			j;
	int			li;
	char		*lst;

	lst = ft_calloc(count_2dvalues(av, ac) + ac, sizeof(char));
	if (!lst)
		return (NULL);
	i = 1;
	li = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
			lst[li++] = av[i][j++];
		lst[li++] = c;
		i++;
	}
	return (lst);
}
