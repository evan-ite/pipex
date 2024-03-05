# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evan-ite <evan-ite@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 14:07:09 by evan-ite          #+#    #+#              #
#    Updated: 2024/02/29 18:02:16 by evan-ite         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = pipex
BONUS = pipex_bonus
LIBFT = libft/libft.a
SRC = src/pipex.c src/errors.c src/free_init.c src/path.c src/processes.c src/utils.c
BSRC = bonus/pipex_bonus.c src/errors.c src/free_init.c src/path.c src/processes.c src/utils.c

OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)

all: libft $(NAME)

bonus: libft $(BONUS)

$(NAME): libft $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBFT)

$(BONUS): libft $(BOBJ)
	rm -f $(NAME)
	$(CC) -o $(BONUS) $(BOBJ) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	$(MAKE) -C libft;

clean:
	rm -f $(OBJ) $(BOBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) $(BONUS) *.gch
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft
