/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:42:12 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/21 12:51:22 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

static void	loop(t_data *data, int n)
{	
	int	k;

	if (data->phs[n].index & 1)
	{
		eat(data, n, n + 1);
		sleep_philo(data, n);
	}
	else
	{
		k = n - 1;
		if (!data->phs[k].has_eaten)
		{
			death_check(data, n);
			if (data->dead)
				return ;
			print_message(n + 1, "is thinking", data, 0);
		}
		eat(data, n, k);
		sleep_philo(data, n);
	}
	data->phs[n].has_eaten = 0;
}

void	*routine(t_data *data)
{
	int				i;
	int				times;

	i = 0;
	times = 0;
	while (data->phs[i].index > 0)
		i++;
	data->phs[i].index = i + 1;
	while (!data->start)
		usleep(300);
	if (data->number_of_meals)
		while (times++ < data->number_of_meals || !data->dead)
			loop(data, i);
	else
		while (!data->dead)
			loop(data, i);
	return (NULL);
}
