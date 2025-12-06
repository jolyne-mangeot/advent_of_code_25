# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmangeot <jmangeot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/05 12:14:14 by jmangeot          #+#    #+#              #
#    Updated: 2025/12/05 12:14:19 by jmangeot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =			main.c
OBJ =			$(SRC:.c=.o)

CFLAGS =		-Wall -Wextra -Werror
NAME =			tester.out
LIBFT =			../Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L../Libft -lft -o $(NAME)

%.o: %.c
	cc $(CFLAGS) -g3 -c $^ -o $@

$(LIBFT):
	cd ../Libft && make

clean:
	rm -f $(OBJ)
	cd ../Libft && make clean

fclean: clean
	rm -f $(NAME)
	cd ../Libft && make fclean

re: fclean all
