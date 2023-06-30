/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:09:16 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/30 11:35:54 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "defines.h"

static void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

int	put_error(int error_id)
{
	if (error_id == ERROR_ARGS)
		ft_putstr_fd("Error: Invalid arguments\n", 2);
	else if (error_id == ERROR_MEM)
		ft_putstr_fd("Error: Not enough memory\n", 2);
	else if (error_id == ERROR_MTX)
		ft_putstr_fd("Error: Unable to initialize mutex\n", 2);
	return (error_id);
}
