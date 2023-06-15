/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:42:12 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/15 17:58:00 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

static void	check_end_of_cycle(t_data *data, int n)
{
	long long	time;

	while (pthread_mutex_lock(&data->end_cycle) != 0)
		usleep(1);
	data->finished += 1;
	pthread_mutex_unlock(&data->end_cycle);
	if (data->finished == data->philo_amount && pthread_mutex_lock(&data->end_cycle) == 0)
	{
		data->finished = 0;
		data->cycle_time = get_time_ms(0);
		pthread_mutex_unlock(&data->end_cycle);
	}
	else
	{
		time = get_time_ms(data->init_time);
		printf(BLUE"[%lld ms]\t"WHITE"%d is thinking\n", time, data->phs[n].index);
		while (data->finished != 0)
			usleep(1);
	}
	data->phs[n].has_eaten = 0;
}

static void	loop(t_data *data, int n)
{	
	int			i;
	long long	time;

	i = 0;
	if (data->phs[n].index & 1)
	{
		sleep_philo(data, n);
		if (data->phs[n + 1].has_eaten < 1)
		{
			time = get_time_ms(data->init_time);
			printf(BLUE"[%lld ms]\t"WHITE"%d is thinking\n", time, data->phs[n].index);
			while (data->phs[n + 1].has_eaten < 1)
				usleep(1);
		}
		eat(data, n, n + 1);
	}
	else
	{
		eat(data, n, n - 1);
		sleep_philo(data, n);
	}
	check_end_of_cycle(data, n);
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
	while (data->start < 1)
		usleep(1);
	data->cycle_time = get_time_ms(0);
	if (data->number_of_meals > 0)
		while (times++ < data->number_of_meals)
			loop(data, i);
	else
		while (1)
			loop(data, i);
	return (NULL);
}
