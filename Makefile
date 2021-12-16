# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/12 23:24:12 by mbouzaie          #+#    #+#              #
#    Updated: 2021/12/03 23:16:00 by mbouzaie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PSWAP_H			= -I includes/
LIBFT_H			= -I $(LIB_DIR)includes/
LIBFT_A			= libft.a

OBJ_DIR			= objs/
SRC_DIR			= srcs/
LIB_DIR			= srcs/libft/
LIBS_DIR		= -L. -L$(LIB_DIR)


SRCS			= main.c
CFIND			= $(SRCS:%=$(SRC_DIR)%)
OFILE			= $(SRCS:%.c=%.o)
OBJS			= $(addprefix $(OBJ_DIR), $(OFILE))



CC				= gcc
RM				= rm -f
CFLAGS			= -g -fsanitize=address -Wall -Wextra -Werror -o
				 
LIBS			= $(CUB3D_H) $(LIBFT_H)

NAME			= libphilo.a
GAME_NAME		= philo


all:			$(OBJ_DIR) $(GAME_NAME)

$(OBJ_DIR):
				@mkdir -p $(OBJ_DIR)

$(GAME_NAME) : $(NAME)
				@$(CC) $(CFLAGS) $(GAME_NAME) $(LIBS_DIR) -lphilo $(LIBS)

$(NAME):		$(OBJS)
				@make -C $(LIB_DIR) bonus
				@cp $(LIB_DIR)$(LIBFT_A) .
				@mv $(LIBFT_A) $(NAME)
				@ar rc $(NAME) $(addprefix $(OBJ_DIR), $(OFILE))
				@ranlib $(NAME)

$(OBJS): $(CFIND)
			@make $(OFILE)

$(OFILE):
			@$(CC) $(LIBS) -c $(CFLAGS) $(OBJ_DIR)$@ $(SRC_DIR)$(@:%.o=%.c)

clean:
				@/bin/rm -rf $(OBJ_DIR)
				@make -C $(LIB_DIR) clean
				@echo object files cleaned

fclean:			clean
				$(RM) $(NAME) $(GAME_NAME)
				@make -C $(LIB_DIR) fclean
				@echo cleaned $(NAME) and object files

re:				fclean all

.PHONY:			all clean fclean re