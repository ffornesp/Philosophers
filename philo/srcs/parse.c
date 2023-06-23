/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:09:23 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/23 11:33:38 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>
#include <limits.h>

static int	check_limits(long j)
{
	int	i;

	if (j > INT_MAX || j < INT_MIN)
		return (0);
	i = (int)j;
	return (i);
}

static int	ft_atol(const char *str)
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

static int	check_digits(char *arg, int *input)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && !i)
			i++;
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
		{
			found_error(input, arg);
			return (-1);
		}
	}
	return (0);
}

static int	check_zeros(char *arg, int *input)
{
	char	*aux;

	aux = arg;
	if (*arg == '+')
		arg++;
	while (*arg == '0')
		arg++;
	if (*arg != '\0')
	{
		found_error(input, aux);
		return (-1);
	}
	return (0);
}

int	check_input(int argc, char *argv[], int *input)
{
	int	i;
	int	n;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '-')
			return (found_error(input, argv[i]));
		if (check_digits(argv[i], input) < 0)
			return (-1);
		n = ft_atol(argv[i]);
		if (n <= 0)
			return (found_error(input, argv[i]));
		if (n == 0)
			if (check_zeros(argv[i], input) < 0)
				return (-1);
		input[i - 1] = n;
		i++;
	}
	if (argc < 6)
		input[4] = 0;
	return (0);
}
