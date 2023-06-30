/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:06:13 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/30 18:26:06 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "philosophers.h"
#include "defines.h"

static void	thread_join(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_amount)
		pthread_join(table->philos[i++].thread_id, NULL);
	pthread_join(table->death_t, NULL);
}

static int	clean_exit(t_table *table)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (i < table->philo_amount)
		error += pthread_mutex_destroy(&(table->forks[i++]));
	error += pthread_mutex_destroy(&(table->data.print_mutex));
	error += pthread_mutex_destroy(&(table->data.start_mutex));
	free(table->philos);
	free(table->forks);
	return (error);
}

int	main(int argc, char *argv[])
{
	t_table	table;
	int		error;

	if (parse(argc, argv, &table))
		return (put_error(ERROR_ARGS));
	error = init_structs(&table);
	if (error)
		return (put_error(error));
	thread_join(&table);
	return (clean_exit(&table));
}
