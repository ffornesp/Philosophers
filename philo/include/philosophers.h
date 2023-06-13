/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:28:46 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/13 16:48:31 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	philo_fork;
	int				index;
}					t_philo;

typedef struct s_data
{
	t_philo	*phs;
	int		philo_amount;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_meals;
}			t_data;

void	input_error(char *str, int i);
void	usage_error(char **argv);
void	other_error(char *str);

long long	get_time_ms(long long init_time);

int		*check_input(int argc, char *argv[]);
#endif
