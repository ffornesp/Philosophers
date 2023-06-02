/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:13:52 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/01 17:32:33 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
		usage_error(argv);
	i = 1;
	while (argv[i])
	{
		if (!check_digits(argv[i]))
			input_error(argv[i]);
		i++;
	}
	return (0);
}