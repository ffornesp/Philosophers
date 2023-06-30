/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:04:26 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/30 18:25:44 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

# define ERROR_ARGS	1
# define ERROR_MEM	2
# define ERROR_MTX	3
# define ERROR_TC	4

# include <pthread.h>

typedef struct s_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				meals_served;
	long long		init_time;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	start_mutex;
	int				dead;
}			t_data;

typedef struct s_philo
{
	int				pid;
	pthread_t		thread_id;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	long long		last_meal;
	int				times_ate;
	t_data			*data;
}					t_philo;

typedef struct s_table
{
	int				philo_amount;
	t_data			data;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_t		death_t;
}					t_table;

#endif
