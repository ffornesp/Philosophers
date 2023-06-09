/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:23:18 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/23 11:34:17 by ffornes-         ###   ########.fr       */
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
}

void	other_error(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		i++;
	write(2, "Error: ", 7);
	write(2, str, i);
}

int	found_error(int *input, char *str)
{
	free(input);
	printf("\"%s\" is not a valid input\n", str);
	return (-1);
}
