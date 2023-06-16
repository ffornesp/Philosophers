/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:27:34 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/16 19:44:15 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

void	death_check(t_data *data, int n)
{
	long long	time;

	time = get_time_ms(data->init_time) - data->phs[n].death_timer;
	time -= data->time_to_die;
	if (time >= 0)
	{
		if (data->dead)
			return ;
		if (!pthread_mutex_lock(&data->death_mutex))
		{
			if (data->dead)
				return ;
			data->dead = 1;
			usleep(1000);
			time = get_time_ms(data->init_time);
			printf(BLUE"[%lld ms]\t"RED"%d has died\n"WHITE, time, data->phs[n].index);
			pthread_mutex_unlock(&data->death_mutex);
		}
	}
	return ;
}

void	sleep_philo(t_data *data, int n)
{
	long long	time;

	time = get_time_ms(data->init_time);
	if (data->dead)
		return ;
	printf(BLUE"[%lld ms]\t"CYAN"%d is sleeping\n"WHITE, time, data->phs[n].index);
	usleep(data->time_to_sleep);
	data->phs[n].has_eaten = 0;
	death_check(data, n);
	time = get_time_ms(data->init_time);
	if (data->dead)
		return ;
	if (data->phs[n].index & 1 && !data->phs[n + 1].has_eaten)
		printf(BLUE"[%lld ms]\t"WHITE"%d is thinking\n"WHITE, time, data->phs[n].index);
}

void	eat(t_data *data, int n, int k)
{
	long long	time;

	while (pthread_mutex_lock(&data->phs[k].philo_fork))
		if (data->dead)
			return ;
	pthread_mutex_lock(&data->phs[n].philo_fork);
	death_check(data, n);
	if (data->dead)
	{
		pthread_mutex_unlock(&data->phs[n].philo_fork);
		pthread_mutex_unlock(&data->phs[k].philo_fork);
		return ;
	}
	time = get_time_ms(data->init_time);
	printf(BLUE"[%lld ms]\t"WHITE"%d"YELLOW" has taken a fork\n"WHITE, time, data->phs[n].index);
	printf(BLUE"[%lld ms]\t"WHITE"%d"YELLOW" has taken a fork\n"WHITE, time, data->phs[n].index);
	printf(BLUE"[%lld ms]\t"GREEN"%d is eating\n"WHITE, time, data->phs[n].index);
	data->phs[n].death_timer = time;
	usleep(data->time_to_eat);
	data->phs[n].has_eaten = 1;
	pthread_mutex_unlock(&data->phs[k].philo_fork);
	pthread_mutex_unlock(&data->phs[n].philo_fork);
}
