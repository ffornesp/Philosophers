/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:42:12 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/14 16:49:10 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

static void	sleep_philo(t_data *data, int n, int times)
{
	if (times < 1 && data->phs[n].index % 2 != 0)
	{
		while (pthread_mutex_unlock(&data->phs[n].philo_fork) != 0)
			usleep(1);
		printf("%d"GREEN" dropped a fork...\n"WHITE, data->phs[n].index);
		data->phs[n].lock = 0;
	}
	printf("%d is sleeping...\n", data->phs[n].index);
	usleep(data->time_to_sleep);
	data->phs[n].has_slept = 1;
}

static void	eat(t_data *data, int n, int k, int times)
{
	while (data->phs[k].lock != 0)
		usleep(1);
	if (times > 0 || (times < 1 && (data->phs[n].index % 2 != 0)))
	{
		while (pthread_mutex_lock(&data->phs[n].philo_fork) != 0)
			usleep(1);
		printf("%d"YELLOW" grabbed a fork...\n"WHITE, data->phs[n].index);
		data->phs[n].lock = 1;
	}
	while (pthread_mutex_lock(&data->phs[k].philo_fork) != 0)
		usleep(1);
	printf("%d"YELLOW" grabbed a fork...\n"WHITE, data->phs[n].index);
	data->phs[k].lock = 1;
	printf("%d is eating...\n", data->phs[n].index);
	usleep(data->time_to_eat);
	data->phs[n].has_eaten = 1;
	
	printf("\t%d had "RED"%d"WHITE" meals\n", data->phs[n].index, times + 1);
	
	if (pthread_mutex_unlock(&data->phs[n].philo_fork) == 0)
		printf("%d"GREEN" dropped a fork...\n"WHITE, data->phs[n].index);
	data->phs[n].lock = 0;
	if (pthread_mutex_unlock(&data->phs[k].philo_fork) == 0)
		printf("%d"GREEN" dropped a fork...\n"WHITE, data->phs[n].index);
	data->phs[k].lock = 0;
}

static void	loop(t_data *data, int n, int times)
{	
	int				i;

	i = 0;
	data->phs[n].has_eaten = 0;
	data->phs[n].has_slept = 0;
	if (data->phs[n].index % 2 != 0)
	{
		sleep_philo(data, n, times);
		eat(data, n, n + 1, times);
	}
	else
	{
		eat(data, n, n - 1, times);
		sleep_philo(data, n, times);
	}
	// Here must wait until other threads finish execution, beaware of data races mate...
	// in order to prevent data races would be nice to have a mutex to let the first thread
	// that finishes execution, check all the other threads for their booleans has_slept && 
	// has eaten in order to determine when it's the end of a full round of philosophing.
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
	if (pthread_mutex_lock(&data->phs[i].philo_fork) != 0)
		printf(RED"Unable to lock mutex\n"WHITE);
	data->phs[i].lock = 1;
	if (data->number_of_meals > 0)
	{
		while (times < data->number_of_meals)
			loop(data, i, times++);
	}
	else
	{
		while (1)
			loop(data, i, times++);
	}
	return (NULL);
}
