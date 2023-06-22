/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:42:12 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/22 15:14:19 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

static void	philo_sleep(t_data *data, int p_id)
{
	if (data->dead)
		return ;
	print_message(p_id + 1, CYAN"is sleeping", data);
	sleep_wrapper(data->time_to_sleep, data, p_id);
}

static void	eat_action(t_data *data, int p_id, int next)
{
	pthread_mutex_lock(&data->phs[p_id].philo_fork);
	print_message(p_id + 1, YELLOW"has taken a fork", data);
	if (data->philo_amount == 1)
	{
		pthread_mutex_unlock(&data->phs[p_id].philo_fork);
		while (!death_check(data, p_id))
			;
		return ;
	}
	pthread_mutex_lock(&data->phs[next].philo_fork);
	print_message(p_id + 1, YELLOW"has taken a fork", data);
	print_message(p_id + 1, GREEN"is eating", data);
	data->phs[p_id].eating = 1;
	data->phs[p_id].death_timer = get_time_ms(data->init_time);
	sleep_wrapper(data->time_to_eat, data, p_id);
	data->phs[p_id].eating = 0;
	pthread_mutex_unlock(&data->phs[p_id].philo_fork);
	pthread_mutex_unlock(&data->phs[next].philo_fork);
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
	if (!death_check(data, p_id))
		eat_action(data, p_id, next);
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
			usleep(300);
		philo_eat(data, i);
		times++;
	}
	return (NULL);
}
