/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:42:12 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/16 17:52:28 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>

static void	loop(t_data *data, int n)
{	
	long long	time;

	if (data->phs[n].index & 1)
	{
		eat(data, n, n + 1);
		sleep_philo(data, n);
	}
	else
	{
		if (data->phs[n - 1].has_eaten < 1)
		{
			death_check(data, n);
			if (data->dead & 1)
				return ;
			time = get_time_ms(data->init_time);
			printf(BLUE"[%lld ms]\t"WHITE"%d is thinking\n", time, data->phs[n].index);
			while (data->phs[n - 1].has_eaten < 1)
				usleep(1);
		}
		eat(data, n, n - 1);
		sleep_philo(data, n);
	}
	data->phs[n].has_eaten = 0;
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
	if (data->number_of_meals > 0)
		while (times++ < data->number_of_meals || data->dead < 1)
			loop(data, i);
	else
		while (data->dead < 1)
			loop(data, i);
	return (NULL);
}
