# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 16:46:56 by ffornes-          #+#    #+#              #
#    Updated: 2023/06/30 18:43:37 by ffornes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = srcs/
SRC_FILES = philosophers.c \
			parse.c errors.c \
			initialize.c threads.c routine.c \
			utils.c

OBJ_DIR = objs/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

DEP_FILES = $(SRC_FILES:.c=.d)
DEPS = $(addprefix $(OBJ_DIR), $(DEP_FILES))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD
RM = rm -f

INCLUDE = -I ./include/

all:	$(NAME) 

$(NAME):	$(OBJ_DIR) $(OBJS)
			$(CC) -fsanitize=thread $(OBJS) -o $@

$(OBJ_DIR):
			@mkdir $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			$(RM) $(OBJS)
			$(RM) $(DEPS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

-include $(DEPS)

.PHONY: all clean fclean re
