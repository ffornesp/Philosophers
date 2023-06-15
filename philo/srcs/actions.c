/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:27:34 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/15 15:19:55 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

void	sleep_philo(t_data *data, int n)
{
	long long	time;

	time = get_time_ms(data->init_time);
	if (time - data->cycle_time >= data->time_to_die)
		printf("\t\t\t%d is DEJJJJJJJJJJJJ\n", data->phs[n].index);
	printf(BLUE"[%lld ms]\t"CYAN"%d is sleeping\n"WHITE, get_time_ms(data->init_time), data->phs[n].index);
	usleep(data->time_to_sleep);
	if (time - data->cycle_time >= data->time_to_die)
		printf("\t\t\t%d is DEJJJJJJJJJJJJ\n", data->phs[n].index);
	data->phs[n].has_slept = 1;
}

void	eat(t_data *data, int n, int k)
{
	long long	time;

	while (pthread_mutex_lock(&data->phs[k].philo_fork) != 0)
		usleep(5);
	data->phs[k].lock = 1;
	if (pthread_mutex_lock(&data->phs[n].philo_fork) != 0)
		printf("WTFWTF\n");
	data->phs[n].lock = 1;
	time = get_time_ms(data->init_time);
	if (time - data->cycle_time >= data->time_to_die)
		printf("\t\t\t%d is DEJJJJJJJJJJJJ\n", data->phs[n].index);
	printf(BLUE"[%lld ms]\t"WHITE"%d"YELLOW" has taken a fork\n"WHITE, time, data->phs[n].index);
	printf(BLUE"[%lld ms]\t"WHITE"%d"YELLOW" has taken a fork\n"WHITE, time, data->phs[n].index);
	printf(BLUE"[%lld ms]\t"GREEN"%d is eating\n"WHITE, time, data->phs[n].index);
	usleep(data->time_to_eat);
	data->phs[n].has_eaten = 1;
	pthread_mutex_unlock(&data->phs[n].philo_fork);
	data->phs[n].lock = 0;
	pthread_mutex_unlock(&data->phs[k].philo_fork);
	data->phs[k].lock = 0;
}
