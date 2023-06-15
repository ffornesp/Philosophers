/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:27:34 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/15 18:38:49 by ffornes-         ###   ########.fr       */
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

/*	Right now death is only checked before or after sleeping...eating which causes issues
 *	if the time_to_eat or time_to_sleep values are way greater than time_of_death
 *	since death messages can not be delayed more than 10ms... So wtf mate(?)
 *
 *
 *	Time of death is determined by the time of the beggining of the last meal so...
 *	Philosophers eat and sleep in this order exactly.
 */
void	sleep_philo(t_data *data, int n)
{
	long long	time;

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
