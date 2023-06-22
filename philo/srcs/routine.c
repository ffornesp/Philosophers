/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:42:12 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/22 13:22:03 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

static int	death_check(t_data *data, int p_id)
{
	long long	time;

	time = get_time_ms(data->init_time) - data->phs[p_id].death_timer;
	time -= data->time_to_die;
	if (time >= 0)
	{
		if (data->dead)
			return (1);
		if (!pthread_mutex_lock(&data->death_mutex))
		{
			if (data->dead)
				return (1);
			data->dead = 1;
			print_message(p_id + 1, RED"has died", data);
			pthread_mutex_unlock(&data->death_mutex);
			return (1);
		}
	}
	return (0);
}

static void	sleep_wrapper(long long time, t_data *data, int p_id)
{
	long long	init_time;

	init_time = get_time_ms(0);
	while (get_time_ms(0) - init_time < time)
	{
		if (data && death_check(data, p_id))
			break ;
		usleep(50);
	}
}

static void	philo_sleep(t_data *data, int p_id)
{
	if (data->dead)
		return ;
	print_message(p_id + 1, CYAN"is sleeping", data);
	sleep_wrapper(data->time_to_sleep, data, p_id);
}

static void	philo_eat(t_data *data, int p_id)
{
	int	next;

	next = p_id + 1;
	if (next >= data->philo_amount)
		next = 0;
	if (data->phs[next].eating)
		print_message(p_id + 1, WHITE"is thinking", data);
	while (!death_check(data, p_id))
		if (!data->phs[next].eating)
			break ;
	if (data->dead)
		return ;
	pthread_mutex_lock(&data->phs[next].philo_fork);
	print_message(p_id + 1, YELLOW"has taken a fork", data);
	pthread_mutex_lock(&data->phs[p_id].philo_fork);
	if (!death_check(data, p_id))
	{
		data->phs[p_id].eating = 1;
		print_message(p_id + 1, YELLOW"has taken a fork", data);
		print_message(p_id + 1, GREEN"is eating", data);
		data->phs[p_id].death_timer = get_time_ms(data->init_time);
		sleep_wrapper(data->time_to_eat, data, p_id);
	}
	pthread_mutex_unlock(&data->phs[p_id].philo_fork);
	pthread_mutex_unlock(&data->phs[next].philo_fork);
	data->phs[p_id].eating = 0;
	philo_sleep(data, p_id);
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
		;
	while (!data->dead)
	{
		if (data->number_of_meals)
			if (times >= data->number_of_meals)
				break ;
		if (i & 1)
			sleep_wrapper(300, NULL, 0); //These guys aint thinkin now
		philo_eat(data, i);
		times++;
	}
	return (NULL);
}
