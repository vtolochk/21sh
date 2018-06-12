# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtolochk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/08 16:22:13 by vtolochk          #+#    #+#              #
#    Updated: 2018/06/12 13:51:13 by vtolochk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = 21sh

HEADER = includes/shell.h

SRCS = srcs/shell.c srcs/env_functions.c srcs/signals.c srcs/shell_loop.c \
srcs/print_prompt.c srcs/mods.c srcs/getters.c srcs/helpers.c \
srcs/cursor/insert_and_delete_char.c  srcs/cursor/cursor_actions.c \
srcs/cursor/moves_1.c srcs/cursor/moves_2.c srcs/history/history.c \
srcs/history/history_helpers.c srcs/cursor/copy_paste_actions.c \
srcs/cursor/cut_command.c srcs/execute_command.c \
srcs/quoting.c srcs/builtins/check_builtins.c srcs/builtins/bi_echo.c \
srcs/builtins/bi_exit.c

OBJ = $(SRCS:.c=.o)

LIBFT = Libft/libft.a

CFLAGS = -Wall -Werror -Wextra -Iincludes

CC = gcc 

all: lib $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ) Libft/libft.a
	gcc $(CFLAGS) -ltermcap $(LIBFT) $(OBJ) -o $(NAME)

lib:
	make -C Libft/

clean: 
	make -C Libft/ clean
	rm -f $(OBJ)

fclean: clean
	make -C Libft/ fclean
	rm -f $(NAME)

re: fclean all
