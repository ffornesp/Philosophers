/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:13:52 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/26 17:57:20 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>

static void	exec_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_amount)
		if (pthread_create(&data->phs[i++].philo, NULL, (void *)routine, data))
			printf("Failed to create thread\n");
	data->init_time = get_time_ms(0);
	data->start = 1;
	i = 0;
	while (i < data->philo_amount)
	{
		if (pthread_join(data->phs[i].philo, NULL))
			printf("Failed to join thread\n");
		pthread_mutex_destroy(&data->phs[i++].philo_fork);
	}
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}

static void	init_data(t_data *data, int *input)
{
	int	i;

	i = 0;
	data->philo_amount = input[0];
	data->time_to_die = input[1];
	data->time_to_eat = input[2];
	data->time_to_sleep = input[3];
	data->number_of_meals = input[4];
	data->init_time = 0;
	data->start = 0;
	pthread_mutex_init(&data->death_mutex, NULL);
	data->dead = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	while (i < data->philo_amount)
	{
		data->phs[i].index = -1;
		data->phs[i].eating = 0;
		data->phs[i].death_timer = 0;
		pthread_mutex_init(&data->phs[i].philo_fork, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data			data;
	int				*input;

	if (argc < 5 || argc > 6)
	{
		usage_error(argv);
		return (0);
	}
	input = malloc(sizeof(int) * argc - 1);
	if (!input)
		return (0);
	if (check_input(argc, argv, input) < 0)
		return (0);
	data.phs = malloc(sizeof(t_philo) * input[0]);
	if (!data.phs)
	{
		free(input);
		other_error("Not able to allocate philosophers\n");
	}
	init_data(&data, input);
	exec_philo(&data);
	free(input);
	free(data.phs);
	return (0);
}
