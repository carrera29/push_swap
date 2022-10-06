# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 13:09:12 by clcarre           #+#    #+#              #
#    Updated: 2022/09/05 11:08:14 by chloeplatt       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  	= push_swap.a 
LIB 	= ar -rcs

SRC		= push_swap.c

OBJS 	= $(SRC:.c=.o)

CFLAGS 	= -Wall -Wextra -Werror

$(NAME) : $(OBJS)
	$(LIB) $(NAME) $(OBJS)
	
all : $(NAME)

gcc $(CFLAGS) -c $< -o $(<:.c=.o)

clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re