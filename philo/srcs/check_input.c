/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:09:23 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/21 13:46:46 by ffornes-         ###   ########.fr       */
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

static void	found_error(int *input, char *str, int i)
{
	free(input);
	input_error(str, i);
}

static void	check_zeros(char *arg, int *input)
{
	char	*aux;

	aux = arg;
	if (*arg == '+')
		arg++;
	while (*arg == '0')
		arg++;
	if (*arg != '\0')
		found_error(input, aux, 0);
}

int	*check_input(int argc, char *argv[])
{
	int	i;
	int	n;
	int	*input;

	i = 1;
	input = malloc(sizeof(int) * argc - 1);
	while (argv[i])
	{
		if (argv[i][0] == '-')
			found_error(input, argv[i], 0);
		n = ft_atol(argv[i]);
		if (n == 0)
			check_zeros(argv[i], input);
		if (n == 1 && i == 1)
			found_error(input, argv[i], 1);
		input[i - 1] = n;
		i++;
	}
	if (argc < 6)
		input[4] = 0;
	return (input);
}
