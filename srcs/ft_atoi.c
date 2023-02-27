/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcocci <pcocci@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:36:33 by pcocci            #+#    #+#             */
/*   Updated: 2023/02/27 11:36:51 by pcocci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	whitespaces(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == 43 && str[i + 1] != 45)
		i++;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == '0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	sign = 1;
	result = 0;
	i = whitespaces(str);
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
}