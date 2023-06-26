/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:09:23 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/26 18:28:18 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

static int	check_digit_amount(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		str++;
	while (str[i] == '0')
		str++;
	while (str[i])
		i++;
	if (i > 11)
		return (0);
	return (1);
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
		if (!check_digit_amount(argv[i]))
			return (found_error(input, argv[i]));
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
