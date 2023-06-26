/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:22:21 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/26 18:25:03 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philosophers.h"

static int	check_limits(long j)
{
	int	i;

	if (j > INT_MAX || j < INT_MIN)
		return (0);
	i = (int)j;
	return (i);
}

int	ft_atol(const char *str)
{
	int		i;
	long	j;

	i = 0;
	j = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			i++;
		if (*(str + 1) == '+' || *(str + 1) == '-')
			return (0);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		j = (j * 10) + (*str - '0');
		str++;
	}
	if (i > 0)
		j *= -1;
	return (check_limits(j));
}
