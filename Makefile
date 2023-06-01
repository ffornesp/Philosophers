# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 16:46:56 by ffornes-          #+#    #+#              #
#    Updated: 2023/06/01 17:26:31 by ffornes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

SRC_DIR = srcs/
SRC_FILES = philosophers.c error_handling.c check_input.c philosophers_utils.c

OBJ_DIR = objs/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

INCLUDE = -I ./include/

all:	$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
			$(CC) $(INCLUDE) $(OBJS) -o $@

$(OBJ_DIR):
			@mkdir $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
