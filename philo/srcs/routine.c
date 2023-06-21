/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:42:12 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/21 16:08:42 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

static void	sleep_wrapper(long long time, t_data *data)
{
	int			i;
	long long	value = time / 4;

	i = 0;
	while (i < 4)
	{
		if (data->dead)
			break ;
		usleep(value);
		i++;
	}
}

static void	philo_sleep(t_data *data, int philo_id)
{
	if (data->dead)
		return ;
	print_message(philo_id + 1, CYAN"is sleeping", data, 0);
	sleep_wrapper(data->time_to_sleep, data);
	//usleep(data->time_to_sleep);
}

static void	philo_eat(t_data *data, int philo_id)
{
	int	next;

	next = philo_id + 1;
	if (next >= data->philo_amount)
		next = 0;
	if (data->phs[next].eating)
		print_message(philo_id + 1, WHITE"is thinking", data, 0);
	pthread_mutex_lock(&data->phs[next].philo_fork);
	pthread_mutex_lock(&data->phs[philo_id].philo_fork);
	if (!data->dead)
	{
		data->phs[philo_id].eating = 1;
		print_message(philo_id + 1, YELLOW"has taken a fork", data, 1);
		data->phs[philo_id].death_timer = get_time_ms(data->init_time);
		sleep_wrapper(data->time_to_eat, data);
		//usleep(data->time_to_eat);
	}
	pthread_mutex_unlock(&data->phs[philo_id].philo_fork);
	pthread_mutex_unlock(&data->phs[next].philo_fork);
	data->phs[philo_id].eating = 0;
	philo_sleep(data, philo_id);
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
		usleep(1);
	while (!data->dead)
	{
		if (data->number_of_meals)
			if (times >= data->number_of_meals)
				break ;
		if (i & 1)
			usleep(300);
		philo_eat(data, i);
		times++;
	}
	return (NULL);
}
