/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:21:48 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/30 18:51:01 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "defines.h"
#include "philosophers.h"

void	*death_check(t_table *table)
{
	int			i;
	int			n;
	long long	time;

	n = table->data.philo_amount;
	while (1 && !table->data.dead)
	{
		i = 0;
		while (i < n)
		{
			time = get_time_ms(table->philos[i].last_meal);
			if (time > table->philos[i].data->time_to_die)
			{
				philo_dead(&table->philos[i]);
				return (NULL);
			}
		}
		usleep_wrapper(100, table->data.dead);
	}
	return (NULL);
}

int	start_threads(t_table *table)
{
	int	i;
	int	n;

	i = 0;
	n = table->data.philo_amount;
	pthread_mutex_lock(&table->data.start_mutex);
	while (i < n)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, \
			(void *)routine, &table->philos[i]))
			return (ERROR_TC);
		table->philos[i++].last_meal = get_time_ms(0);
	}
	table->data.init_time = get_time_ms(0);
	pthread_mutex_unlock(&table->data.start_mutex);
	return (0);
}
