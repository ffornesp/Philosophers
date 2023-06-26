/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:27:34 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/26 18:10:14 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

static void	death_message(int n, char *str, t_data *data)
{
	long long	time;

	time = get_time_ms(data->init_time);
	if (!pthread_mutex_lock(&data->print_mutex))
		printf(BLUE"[%04lld ms]\t"WHITE"%d %s\n"WHITE, time, n, str);
	pthread_mutex_unlock(&data->print_mutex);
}

int	death_check(t_data *data, int p_id)
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
			{
				pthread_mutex_unlock(&data->death_mutex);
				return (1);
			}
			data->dead = 1;
			death_message(p_id + 1, RED"has died", data);
			pthread_mutex_unlock(&data->death_mutex);
			return (1);
		}
	}
	return (0);
}

void	sleep_wrapper(long long time, t_data *data, int p_id)
{
	long long	init_time;

	init_time = get_time_ms(0);
	while (get_time_ms(0) - init_time < time)
	{
		if (data && death_check(data, p_id))
			break ;
		if (data && data->dead)
			break ;
		usleep(50);
	}
}

void	print_message(int n, char *str, t_data *data)
{
	long long	time;

	if (!data->dead)
	{
		time = get_time_ms(data->init_time);
		if (!pthread_mutex_lock(&data->print_mutex) && !data->dead)
			printf(BLUE"[%04lld ms]\t"WHITE"%d %s\n"WHITE, time, n, str);
		pthread_mutex_unlock(&data->print_mutex);
	}
}

long long	get_time_ms(long long init_time)
{
	long long		current_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	current_time -= init_time;
	return (current_time);
}
