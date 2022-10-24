# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 13:09:12 by clcarre           #+#    #+#              #
#    Updated: 2022/10/24 15:20:47 by chloeplatt       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  	= 	push_swap.a
CFLAGS 	= 	-Wall -Wextra -Werror

OBJ_PAT =	./obj/
SRC		= 	./src/push_swap.c \
			./src/check_in.c \
			./src/ft_split.c \
			./src/long_stack.c \
			./src/move_numbers.c \
			./src/utils.c

OBJS 	= 	$(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	ar -rcs $(NAME) $(OBJS)

.c.o :
	gcc $(CFLAGS) -c $< -o $(<:.c=.o)
	
clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re