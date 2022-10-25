# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chloeplatt <chloeplatt@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 13:09:12 by clcarre           #+#    #+#              #
#    Updated: 2022/10/25 17:49:02 by chloeplatt       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  	= $(BIN_DIR)/push_swap.a
SRC_DIR	= ./src
OBJ_DIR	= ./obj
INC_DIR	= ./include
BIN_DIR	= ./bin
SRC		= 	$(SRC_DIR)/push_swap.c \
			$(SRC_DIR)/check_in.c \
			$(SRC_DIR)/ft_split.c \
			$(SRC_DIR)/long_stack.c \
			$(SRC_DIR)/move_numbers.c \
			$(SRC_DIR)/utils.c		
OBJ 	= 	$(SRC:.c=.o)

# -I incluye la ruta del *.h
CFLAGS 	= 	-Wall -Wextra -Werror -I$(INC_DIR)

$(NAME) : $(OBJ)
	mkdir -p $(BIN_DIR)
	ar -rcs $(NAME) $(OBJ) 

%.o : %.c
	gcc -c $(CFLAGS) $< -o $@
	gcc $(CFLAGS) $(SRC) -o push_swap
# -include $(OBJ_DIR)/*.d

all : $(NAME)

clean : 
	rm -f $(OBJ)
# rm -r $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)
	rm -r $(BIN_DIR)
	rm -f push_swap

re : fclean all

# indica que son acciones, no archivos que deban generarse
.PHONY : all clean fclean re