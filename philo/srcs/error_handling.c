/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:23:18 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/13 13:05:04 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	usage_error(char **argv)
{
	printf("Usage: %s", argv[0]);
	printf(" \"number_of_philosophers\"");
	printf(" \"time_to_die\"");
	printf(" \"time_to_eat\"");
	printf(" \"time_to_sleep\"");
	printf(" optional:");
	printf(" \"[number_of_times_each_philosopher_must_eat]\"\n");
	exit(0);
}

void	input_error(char *str, int i)
{
	if (i < 1)
		printf("\"%s\" is not a valid input\n", str);
	else
		printf("number_of_philosophers (\"%s\") must be at least 2\n", str);
	exit(0);
}

void	other_error(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		i++;
	write(2, "Error: ", 7);
	write(2, str, i);
	exit(1);
}
