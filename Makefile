# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtolochk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/08 16:22:13 by vtolochk          #+#    #+#              #
#    Updated: 2018/05/08 16:44:45 by vtolochk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = 21sh

HEADER = includes/sh21.h

SRCS = srcs/main.c

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
