/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:27:34 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/15 16:52:13 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

static void	death_check(t_data *data, int n)
{
	long long	time;

	if (get_time_ms(data->cycle_time) >= data->time_to_die)
	{
		time = get_time_ms(data->init_time);
		printf(BLUE"[%lld ms]\t"RED"%d has died\n"WHITE, time, data->phs[n].index);
	}
}

void	sleep_philo(t_data *data, int n)
{
	long long	time;

	death_check(data, n);
	time = get_time_ms(data->init_time);
	printf(BLUE"[%lld ms]\t"CYAN"%d is sleeping\n"WHITE, time, data->phs[n].index);
	usleep(data->time_to_sleep);
	death_check(data, n);
}

void	eat(t_data *data, int n, int k)
{
	long long	time;

	while (pthread_mutex_lock(&data->phs[k].philo_fork) != 0)
		usleep(1);
	if (pthread_mutex_lock(&data->phs[n].philo_fork) != 0)
		printf("WTFWTF\n");
	death_check(data, n);
	time = get_time_ms(data->init_time);
	printf(BLUE"[%lld ms]\t"WHITE"%d"YELLOW" has taken a fork\n"WHITE, time, data->phs[n].index);
	printf(BLUE"[%lld ms]\t"WHITE"%d"YELLOW" has taken a fork\n"WHITE, time, data->phs[n].index);
	printf(BLUE"[%lld ms]\t"GREEN"%d is eating\n"WHITE, time, data->phs[n].index);
	usleep(data->time_to_eat);
	death_check(data, n);
	data->phs[n].has_eaten = 1;
	pthread_mutex_unlock(&data->phs[n].philo_fork);
	pthread_mutex_unlock(&data->phs[k].philo_fork);
}
