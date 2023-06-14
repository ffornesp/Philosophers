/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:42:12 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/14 14:55:03 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

static void	sleep_philo(t_data *data, int n)
{
	while (pthread_mutex_unlock(&data->phs[n].philo_fork) != 0)
		usleep(5);
	printf("%d"GREEN" dropped a fork...\n"WHITE, data->phs[n].index);
	printf("%d is sleeping...\n", data->phs[n].index);
	usleep(data->time_to_sleep);
}

static void	eat(t_data *data, int n, int k)
{
	while (pthread_mutex_lock(&data->phs[n].philo_fork) != 0)
		usleep(5);
	printf("%d"YELLOW" grabbed a fork...\n"WHITE, data->phs[n].index);
	while (pthread_mutex_lock(&data->phs[k].philo_fork) != 0)
		usleep(5);
	printf("%d"YELLOW" grabbed a fork...\n"WHITE, data->phs[n].index);
	printf("%d is eating...\n", data->phs[n].index);
	usleep(data->time_to_eat);
	if (pthread_mutex_unlock(&data->phs[k].philo_fork) == 0)
		printf("%d"GREEN" dropped a fork...\n", data->phs[n].index);
}

void *routine(t_data *data)
{
	int	i;

	i = 0;
	while (data->phs[i].index > 0)
		i++;
	data->phs[i].index = i + 1;
	if (pthread_mutex_lock(&data->phs[i].philo_fork) != 0)
		printf(RED"Unable to lock mutex\n"WHITE);

	if (data->phs[i].index % 2 != 0)
	{
		sleep_philo(data, i);
		eat(data, i, i + 1);
	}
	else
	{
		eat(data, i, i - 1);
		sleep_philo(data, i);
	}
}
