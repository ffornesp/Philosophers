/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:28:46 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/30 18:54:03 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include "defines.h"

int			parse(int argc, char *argv[], t_table *table);
int			init_structs(t_table *table);
int			start_threads(t_table *table);

void		*routine(t_philo *philo);
void		meal_count(t_philo *philo);
void		*death_check(t_table *table);
void		*philo_dead(t_philo *philo);

int			print_message(t_philo *philo, char *str, int death, int meal);
long long	get_time_ms(long long init_time);
void		usleep_wrapper(long long time, int dead);
int			put_error(int error_id);

#endif
