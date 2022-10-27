# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 13:09:12 by clcarre           #+#    #+#              #
#    Updated: 2022/10/27 12:58:34 by chloeplatt       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  	= push_swap

SRC_DIR	= ./src
INC_DIR	= ./include

SRC		= 	$(SRC_DIR)/push_swap.c \
			$(SRC_DIR)/check_in.c \
			$(SRC_DIR)/ft_split.c \
			$(SRC_DIR)/long_stack.c \
			$(SRC_DIR)/move_numbers.c \
			$(SRC_DIR)/utils.c		

OBJ 	= 	$(SRC:.c=.o)

CFLAGS 	= 	-Wall -Wextra -Werror -I$(INC_DIR)

$(NAME) : $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(NAME)

%.o : /%.c
	@gcc -c $(CFLAGS) $< -o $@

all : $(NAME)

clean : 
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re