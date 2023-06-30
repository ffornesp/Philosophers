/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:26:42 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/30 18:21:54 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "philosophers.h"
#include <pthread.h>

void	*philo_dead(t_philo *philo)
{
	if (philo->data->dead)
		return (NULL);
	philo->data->dead = 1;
	print_message(philo, RED"died\n", 1);
	return (NULL);
}

static int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_message(philo, YELLOW"has taken a fork", 0);
	if (!philo->fork_right)
		return (1);
	pthread_mutex_lock(philo->fork_right);
	print_message(philo, YELLOW"has taken a fork", 0);
	print_message(philo, GREEN"is eating", 0);
	philo->times_ate++;
	philo->last_meal = get_time_ms(0);
	usleep_wrapper(philo->data->time_to_eat, philo->data->dead);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

void	*routine(t_philo *philo)
{
	if ((philo->pid + 1) % 2)
	{
		print_message(philo, WHITE"is thinking", 0);
		usleep_wrapper(200, philo->data->dead);
	}
	pthread_mutex_lock(&philo->data->start_mutex);
	pthread_mutex_unlock(&philo->data->start_mutex);
	while (!philo->data->dead)
	{
		if (philo_eat(philo))
			return (NULL);
		print_message(philo, CYAN"is sleeping", 0);
		usleep_wrapper(philo->data->time_to_sleep, philo->data->dead);
		print_message(philo, WHITE"is thinking", 0);
		if (philo->data->number_of_meals > 0 && \
			philo->times_ate >= philo->data->number_of_meals)
			philo->data->dead = 1;
	}
	return (NULL);
}
