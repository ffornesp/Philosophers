/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:23:18 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/01 16:31:14 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	usage_error(char **argv)
{
	printf("Usage: %s", argv[0]);
	printf(" \"number_of_philosophers\"");
	printf(" \"time_to_die\"");
	printf(" \"time_to_eat\"");
	printf(" \"time_to_sleep\"");
	printf(" optional:");
	printf(" \"[number_of_times_each_philosopher_must_eat]\"\n");
}
