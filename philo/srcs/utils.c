/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:27:34 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/22 12:21:04 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

void	print_message(int n, char *str, t_data *data)
{
	long long	time;

	time = get_time_ms(data->init_time);
	if (!pthread_mutex_lock(&data->print_mutex))
		printf(BLUE"[%04lld ms]\t"WHITE"%d %s\n", time, n, str);
	pthread_mutex_unlock(&data->print_mutex);
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
