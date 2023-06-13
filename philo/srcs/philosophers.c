/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:13:52 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/13 14:17:25 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	pthread_t		philosopher;
	pthread_mutex_t	philo_fork;
	int				index;
}					t_philo;

static long long	get_time_ms(long long init_time)
{
	long long		current_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	current_time -= init_time;
	return (current_time);
}

void	*routine(void)
{
	printf("Hello\n");
	return NULL;
}

static void	exec_philo(int *input, long long init_time, t_philo *ph)
{
	int			i;

	i = 0;
	while (i < input[0])
		pthread_create(&ph[i++].philosopher, NULL, (void *)routine, NULL);
	i = 0;
	while (i < input[0])
		pthread_join(ph[i++].philosopher, NULL);
	printf("Final time: %lld\n", get_time_ms(init_time));
}

int	main(int argc, char *argv[])
{
	int				*input;
	struct timeval	tv;
	long long		init_time;
	t_philo			*philosophers;

	if (argc < 5 || argc > 6)
		usage_error(argv);
	input = check_input(argc, argv);
	gettimeofday(&tv, NULL);
	init_time = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	philosophers = malloc(sizeof(t_philo) * input[0]);
	if (!philosophers)
	{
		free(input);
		other_error("Not able to allocate philosophers\n");
	}
	exec_philo(input, init_time, philosophers);
	free(input);
	return (0);
}
