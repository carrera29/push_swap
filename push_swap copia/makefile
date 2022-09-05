# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clcarre <clcarrer@student.42madrid.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 13:09:12 by clcarre           #+#    #+#              #
#    Updated: 2022/07/13 13:36:33 by clcarre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  	= push_swap.a 
LIB 	= ar -rcs

SRC		= push_swap.c

OBJS 	= $(SRC:.c=.o)

CFLAGS 	= -Wall -Wextra -Werror

$(NAME) : $(OBJS)
	$(LIB) $(NAME) $(OBJS)

.c.o :
	gcc $(CFLAGS) -c $< -o $(<:.c=.o)

all : $(NAME)

clean : 
	rm -f $(OBJS) $(OBJS_B)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re