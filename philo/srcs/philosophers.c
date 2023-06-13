/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:13:52 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/13 15:05:36 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "philosophers.h"
#include <stdlib.h>

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	philo_fork;
	int				index;
}					t_philo;

typedef struct s_data
{
	t_philo	*phs;
	int		*input;
}			t_data;

static long long	get_time_ms(long long init_time)
{
	long long		current_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	current_time -= init_time;
	return (current_time);
}

void	*routine(t_data *data)
{
	int		i;
	int		my_index;

	i = 0;
	while (data->phs[i].index > 0)
		i++;
	my_index = i;
	data->phs[i].index = i + 1;
	printf("Hello from index %d\n", data->phs[my_index].index);
	return (NULL);
}

static void	exec_philo(t_data data, long long init_time)
{
	int			i;

	i = 0;
	while (i < data.input[0])
		pthread_create(&data.phs[i++].philo, NULL, (void *)routine, &data);
	i = 0;
	while (i < data.input[0])
		pthread_join(data.phs[i++].philo, NULL);
	printf("Final time: %lld\n", get_time_ms(init_time));
}

int	main(int argc, char *argv[])
{
	struct timeval	tv;
	long long		init_time;
	t_data			data;
	int				i;

	i = 0;
	if (argc < 5 || argc > 6)
		usage_error(argv);
	data.input = check_input(argc, argv);
	gettimeofday(&tv, NULL);
	init_time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	data.phs = malloc(sizeof(t_philo) * data.input[0]);
	if (!data.phs)
	{
		free(data.input);
		free(data.phs);
		other_error("Not able to allocate philosophers\n");
	}
	while (i < data.input[0])
		data.phs[i++].index = -1;
	exec_philo(data, init_time);
	free(data.input);
	free(data.phs);
	return (0);
}
