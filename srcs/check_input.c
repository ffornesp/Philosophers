/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:23:54 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/01 17:28:30 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_digits(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (!ft_isdigit(*(str + i)))
			return (0);
		i++;
	}
	return (1);
}
