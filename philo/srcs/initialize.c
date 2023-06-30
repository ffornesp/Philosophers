/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:01:19 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/30 18:53:07 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "philosophers.h"
#include "defines.h"

/*
 * Philosophers sit at the table clockwise. So the next philosopher will always
 * be at the left side. That's why we assume that our right fork is from the
 * philosopher before us, not the next one.
 * Assigns forks from the table to the philosophers. Each philosophers brings
 * his left fork and checks that the philosopher before him has his fork too.
 * If there's only one philosopher, no forks can be found on the right.
 */
static void	set_forks(t_philo *philo, pthread_mutex_t *forks, int n)
{
	philo->fork_left = &forks[philo->pid - 1];
	if (philo->pid == 1)
		philo->fork_right = &forks[n - 1];
	else
		philo->fork_right = &forks[philo->pid - 2];
	if (n == 1)
		philo->fork_right = NULL;
}

static int	init_mutex(t_table *table)
{
	int	i;
	int	n;

	n = table->data.philo_amount;
	table->forks = malloc(sizeof(pthread_mutex_t) * n);
	if (table->forks == NULL)
		return (ERROR_MEM);
	if (pthread_mutex_init(&table->data.start_mutex, NULL))
		return (ERROR_MTX);
	if (pthread_mutex_init(&table->data.print_mutex, NULL))
		return (ERROR_MTX);
	i = 0;
	while (i < n)
		if (pthread_mutex_init(&table->forks[i++], NULL))
			return (ERROR_MTX);
	return (0);
}

static int	init_threads(t_table *table)
{
	int	i;
	int	n;

	n = table->data.philo_amount;
	table->philos = malloc(sizeof(t_philo) * n);
	if (table->philos == NULL)
		return (ERROR_MEM);
	i = 0;
	while (i < n)
	{
		table->philos[i].pid = i + 1;
		table->philos[i].times_ate = 0;
		set_forks(&table->philos[i], table->forks, n);
		table->philos[i++].data = &table->data;
		table->data.dead = 0;
		table->data.meals_served = 0;
	}
	if (start_threads(table))
		return (ERROR_TC);
	if (pthread_create(&table->death_t, NULL, (void *)death_check, table))
		return (ERROR_TC);
	return (0);
}

int	init_structs(t_table *table)
{
	int	error;

	error = init_mutex(table);
	if (!error)
		init_threads(table);
	if (error)
		return (error);
	return (0);
}
