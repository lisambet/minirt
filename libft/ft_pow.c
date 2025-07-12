/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 01:52:37 by scraeyme          #+#    #+#             */
/*   Updated: 2025/04/14 02:05:53 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_pow(double nb, double power)
{
	double	tmp;
	int		is_neg;

	if (!power)
		return (1);
	tmp = 0;
	is_neg = power < 0;
	while (power)
	{
		if (!tmp)
			tmp = nb;
		else
			nb *= tmp;
		if (!is_neg)
			power--;
		else
			power++;
	}
	if (is_neg)
		return (1 / nb);
	return (nb);
}
