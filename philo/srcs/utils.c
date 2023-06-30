/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:04:30 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/30 18:54:59 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "philosophers.h"

void	meal_count(t_philo *philo)
{
	static int	count;

	count++;
	if (count >= philo->data->philo_amount)
	{
		count = 0;
		philo->data->meals_served++;
	}
}

void	usleep_wrapper(long long time, int dead)
{
	long long	init_time;

	init_time = get_time_ms(0);
	while (!dead)
	{
		if ((get_time_ms(0) - init_time) >= time)
			break ;
		usleep(10);
	}
}

int	print_message(t_philo *philo, char *str, int death, int meal)
{
	if (pthread_mutex_lock(&philo->data->print_mutex))
		return (1);
	if (!philo->data->dead || death)
	{
		if (meal)
			meal_count(philo);
		printf(BLUE"[%04lld ms]\t"WHITE"[%03d] %s\n"WHITE, \
		get_time_ms(philo->data->init_time), \
		philo->pid, str);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	if (pthread_mutex_unlock(&philo->data->print_mutex))
		return (1);
	return (0);
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


