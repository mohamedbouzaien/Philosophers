# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/12 23:24:12 by mbouzaie          #+#    #+#              #
#    Updated: 2021/12/29 13:52:16 by mbouzaie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADERS			= -I incs/

OBJ_DIR			= objs/
SRC_DIR			= srcs/


SRCS			= main.c utils.c
CFIND			= $(SRCS:%=$(SRC_DIR)%)
OFILE			= $(SRCS:%.c=%.o)
OBJS			= $(addprefix $(OBJ_DIR), $(OFILE))



CC				= gcc
RM				= rm -f
CFLAGS			= -g -fsanitize=thread -Wall -Wextra -Werror -o

NAME			= philo


all:			$(OBJ_DIR) $(NAME)

$(OBJ_DIR):
				mkdir -p $(OBJ_DIR)

$(NAME):		$(OBJS)
				$(CC) -lpthread $(CFLAGS) $(NAME) $(HEADERS) $(OBJS)


$(OBJS): $(CFIND)
			make $(OFILE)

$(OFILE):
			$(CC) $(HEADERS) -c $(CFLAGS) $(OBJ_DIR)$@ $(SRC_DIR)$(@:%.o=%.c)

clean:
				$(RM) -r $(OBJ_DIR)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re