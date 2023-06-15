/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:13:52 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/15 11:38:37 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>

static void	exec_philo(t_data data, long long init_time)
{
	int	i;
	int	j;

	i = 0;
	while (i < data.philo_amount)
	{
		j = pthread_create(&data.phs[i++].philo, NULL, (void *)routine, &data);
		if (j != 0)
			printf("Failed to create thread\n");
	}
	i = 0;
	while (i < data.philo_amount)
	{
		j = pthread_join(data.phs[i].philo, NULL);
		pthread_mutex_destroy(&data.phs[i++].philo_fork);
		if (j != 0)
			printf("Failed to join thread\n");
	}
	printf("Final time: %lld\n", get_time_ms(init_time));
}

static void	init_data(t_data *data, int *input)
{
	int	i;

	i = 0;
	data->philo_amount = input[0];
	data->time_to_die = input[1];
	data->time_to_eat = input[2];
	data->time_to_sleep = input[3];
	data->number_of_meals = 0;
	pthread_mutex_init(&data->end_cycle, NULL);
	data->finished = 0;
	if (input[4] > 0)
		data->number_of_meals = input[4];
	while (i < data->philo_amount)
	{
		data->phs[i].index = -1;
		data->phs[i].has_eaten = 0;
		data->phs[i].has_slept = 0;
		pthread_mutex_init(&data->phs[i].philo_fork, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	long long		init_time;
	t_data			data;
	int				*input;

	if (argc < 5 || argc > 6)
		usage_error(argv);
	input = check_input(argc, argv);
	init_time = get_time_ms(0);
	data.phs = malloc(sizeof(t_philo) * input[0]);
	if (!data.phs)
	{
		free(input);
		free(data.phs);
		other_error("Not able to allocate philosophers\n");
	}
	init_data(&data, input);
	exec_philo(data, init_time);
	free(input);
	free(data.phs);
	return (0);
}
