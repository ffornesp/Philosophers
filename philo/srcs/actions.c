/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:27:34 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/21 12:37:55 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

void	print_message(int n, char *str, t_data *data, int m_id)
{
	long long	time;

	time = get_time_ms(data->init_time);
	if (!pthread_mutex_lock(&data->print_mutex))
	{
		if (!m_id)
			printf(BLUE"[%lld ms]\t"WHITE"%d %s\n", time, n, str);
		else
		{
			printf(BLUE"[%lld ms]\t"WHITE"%d %s\n", time, n, str);
			printf(BLUE"[%lld ms]\t"WHITE"%d %s\n", time, n, str);
			str = GREEN"is eating";
			printf(BLUE"[%lld ms]\t"WHITE"%d %s\n", time, n, str);
		}
	}
	pthread_mutex_unlock(&data->print_mutex);
}

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
			usleep(300);
			print_message(n + 1, RED"has died", data, 0);
			pthread_mutex_unlock(&data->death_mutex);
		}
	}
	return ;
}

void	sleep_philo(t_data *data, int n)
{

	if (data->dead)
		return ;
	print_message(n + 1, CYAN"is sleeping", data, 0);
	usleep(data->time_to_sleep);
	data->phs[n].has_eaten = 0;
	death_check(data, n);
	if (data->dead)
		return ;
	if (data->phs[n].index & 1 && !data->phs[n + 1].has_eaten)
		print_message(n + 1, WHITE"is thinking", data, 0);
}

void	eat(t_data *data, int n, int k)
{
	if (!pthread_mutex_lock(&data->phs[k].philo_fork))
		if (data->dead)
			return ;
	pthread_mutex_lock(&data->phs[n].philo_fork);
	death_check(data, n);
	if (!data->dead)
	{
		print_message(n + 1, YELLOW"has taken a fork", data, 1);
		data->phs[n].death_timer = get_time_ms(data->init_time);
		usleep(data->time_to_eat);
		data->phs[n].has_eaten = 1;
	}
	pthread_mutex_unlock(&data->phs[k].philo_fork);
	pthread_mutex_unlock(&data->phs[n].philo_fork);
}
