/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:13:52 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/02 11:27:25 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	*input;

	if (argc < 5 || argc > 6)
		usage_error(argv);
	input = check_input(argc, argv);



	free(input);
	return (0);
}
