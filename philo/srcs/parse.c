/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:08:43 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/30 18:27:04 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <limits.h>

static int	check_and_set(char *str, int *dst)
{
	int		i;
	int		n_flag;
	long	out;

	i = 0;
	n_flag = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			n_flag = -1;
	if (str[i] == '\0')
		return (ERROR_ARGS);
	out = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (ERROR_ARGS);
		out = (out * 10) + (str[i++] - '0');
	}
	*dst = out * n_flag;
	if ((out * n_flag) > INT_MAX || (out * n_flag) < INT_MIN)
		return (ERROR_ARGS);
	return (0);
}

int	parse(int argc, char *argv[], t_table *table)
{
	if (argc < 5 || argc > 6)
		return (ERROR_ARGS);
	if (check_and_set(argv[1], &table->philo_amount) || \
		check_and_set(argv[2], &table->data.time_to_die) || \
		check_and_set(argv[3], &table->data.time_to_eat) || \
		check_and_set(argv[4], &table->data.time_to_sleep))
		return (ERROR_ARGS);
	table->data.number_of_meals = 0;
	if (argc > 5)
		if (check_and_set(argv[5], &table->data.number_of_meals))
			return (ERROR_ARGS);
	if (table->philo_amount < 1)
		return (ERROR_ARGS);
	if (table->data.time_to_die < 1 || table->data.time_to_eat < 1 || \
		table->data.time_to_sleep < 1)
		return (ERROR_ARGS);
	return (0);
}
