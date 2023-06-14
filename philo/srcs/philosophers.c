/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:13:52 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/14 14:55:05 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"
#include <stdlib.h>
#include <stdio.h>

/*	First drop the forks from even philosophers since philos start at 1 and
 *	continue until data->philo_amount... This way we drop the fork first and
 *	the second philosopher can grab it and starting eating...
 
void	*routine(t_data *data)
{
	int		i;

	i = 0;
	while (data->phs[i].index > 0)
		i++;
	data->phs[i].index = i + 1;
	if (pthread_mutex_lock(&data->phs[i].philo_fork) != 0)
		printf("Unable to lock mutex\n");
	if ((i + 1) % 2 != 0)
	{
		if (pthread_mutex_unlock(&data->phs[i].philo_fork) == 0)
			printf("%d"GREEN" dropped a fork...\n"WHITE, i + 1);
		printf("%d is sleeping...\n", i + 1);
		usleep(data->time_to_sleep);

		while (pthread_mutex_lock(&data->phs[i].philo_fork) != 0)
			usleep(5);
		printf("%d"YELLOW" grabbed a fork...\n"WHITE, i + 1);
		while (pthread_mutex_lock(&data->phs[i + 1].philo_fork) != 0)
			usleep(5);
		printf("%d"YELLOW" grabbed a fork...\n"WHITE, i + 1);
		printf("%d is eating...\n", i + 1);
		usleep(data->time_to_eat);
		if (pthread_mutex_unlock(&data->phs[i].philo_fork) == 0)
			printf("%d"GREEN" dropped a fork...\n"WHITE, i + 1);
		if (pthread_mutex_unlock(&data->phs[i + 1].philo_fork) == 0)
			printf("%d"GREEN" dropped a fork...\n"WHITE, i + 1);

		printf("%d Has finished\n", i + 1);
	}
	else if (i > 0)
	{
		usleep(60);
		if (pthread_mutex_lock(&data->phs[i - 1].philo_fork) == 0)
			printf("%d"YELLOW" grabbed a fork...\n"WHITE, i + 1);
		printf("%d is eating...\n", i + 1);
		usleep(data->time_to_eat);
		if (pthread_mutex_unlock(&data->phs[i].philo_fork) == 0)
			printf("%d"GREEN" dropped a fork...\n"WHITE, i + 1);
		if (pthread_mutex_unlock(&data->phs[i - 1].philo_fork) == 0)
			printf("%d"GREEN" dropped a fork...\n"WHITE, i + 1);

		printf("%d is sleeping...\n", i + 1);
		usleep(data->time_to_sleep);

		printf("%d Has finished\n", i + 1);
	}
	return (NULL);
}
*/

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
	if (input[4] > 0)
		data->number_of_meals = input[4];
	while (i < data->philo_amount)
	{
		data->phs[i].index = -1;
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
