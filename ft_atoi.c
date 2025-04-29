/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astoiber <astoiber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:54:50 by astoiber          #+#    #+#             */
/*   Updated: 2024/09/17 12:37:58 by astoiber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	int		result;
	char	*cnptr;

	i = 0;
	sign = 1;
	result = 0;
	cnptr = (char *)nptr;
	while ((cnptr[i] > 8 && cnptr[i] < 14) || cnptr[i] == ' ')
		i++;
	if (cnptr[i] == '-' || cnptr[i] == '+')
	{
		if (cnptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (cnptr[i] >= '0' && cnptr[i] <= '9')
	{
		result = result * 10 + (cnptr[i] - '0');
		i++;
	}
	return (result * sign);
}
/*
int	main(void)
{
	char	str[] = 0;

	printf("%i :ft\n", ft_atoi(str));
	printf("%i :atoi", atoi(str));
	return (0);
}
*/
