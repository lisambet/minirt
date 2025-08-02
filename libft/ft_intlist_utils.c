/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huvillat <huvillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:10:10 by csenelle          #+#    #+#             */
/*   Updated: 2025/02/04 11:20:06 by huvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_int_set(int *set, int count, int value)
{
	int	i;

	i = 0;
	while (i < count)
		if (set[i++] == value)
			return (1);
	return (0);
}

void	ft_add_set(int v, int count, int *set)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (set[i] == -1)
		{
			set[i] = v;
			break ;
		}
		i++;
	}
}
