# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/12 23:24:12 by mbouzaie          #+#    #+#              #
#    Updated: 2021/12/16 20:58:55 by mbouzaie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = clang

FLAGS = -g -fsanitize=address -Wall -Wextra -Werror

SRCS = srcs/main.c

OBJS = $(SRCS:.cpp=.o)

HEADER_PATH = incs/

SRCS_PATH = srcs/

HEADER_INCS = philosophers.h

all		: 	$(NAME)

$(NAME)	:	$(OBJS)
			@$(CC) -o $(NAME) $(FLAGS) $(OBJS)

$(OBJS)	:	$(addprefix $(HEADER_PATH), $(HEADER_INCS))

clean	:	
				@rm -rf $(OBJS)

fclean	:	clean
				@rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

%.o		:	%.c
			@$(CC) $(FLAGS) -o $@ -c $<