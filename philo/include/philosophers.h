/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:28:46 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/21 16:09:13 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

# include <pthread.h>

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	philo_fork;
	int				index;
	int				eating;
	long long		death_timer;
}					t_philo;

typedef struct s_data
{
	t_philo			*phs;
	int				philo_amount;
	int				time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				number_of_meals;

	long long		init_time;
	int				start;

	pthread_mutex_t	print_mutex;

	pthread_mutex_t	death_mutex;
	int				dead;
}			t_data;

int			*check_input(int argc, char *argv[]);
void		input_error(char *str, int i);
void		usage_error(char **argv);
void		other_error(char *str);

long long	get_time_ms(long long init_time);
void		print_message(int n, char *str, t_data *data, int m_id);

void		*routine(t_data *data);
#endif
