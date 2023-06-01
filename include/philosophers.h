/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:28:46 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/01 17:30:36 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

void	input_error(char *str);
void	usage_error(char **argv);

int		check_digits(char *str);
int		ft_isdigit(int i);
int		ft_atoi(const char *str);

#endif
