# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: annamarianunes <annamarianunes@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/18 19:14:36 by annamarianu       #+#    #+#              #
#    Updated: 2024/05/18 19:46:52 by annamarianu      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g -pthread -fsanitize=thread

SRC_DIR	=	src
SRC		=	main.c handle_input.c data.c forks.c args.c philosophers.c \
			routine.c actions.c dead_checker.c $(UTILS)
UTILS	=	time.c utils.c utils_libft.c clean.c
HEADER	=	philosophers.h

OBJ_DIR	=	.obj
OBJ		=	$(SRC:%.c=$(OBJ_DIR)/%.o)

VPATH	=	src
INCLUDE	=	-I ./


all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@
	@echo "\033[1;32m"
	@echo "************************************"
	@echo "           philo created"
	@echo "************************************"
	@echo "\033[0m"

$(OBJ_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE) 

$(OBJ_DIR):
	mkdir -p $@

run: $(NAME)
	./$(NAME) 5 410 200 200 5
	./$(NAME) 4 400 200 200 5
	./$(NAME) 4 410 200 200 5
#	./$(NAME) 7 400 100 100 5
#	./$(NAME) 5 2000 1000 100 5
#	./$(NAME) 5 2000 100 1000 5

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;32m[OK]\033[0m    \033[0;38;5;44mRemoving objects\033[0m"

fclean:	clean
	@rm -rf $(NAME)
	@echo "\033[0;32m[OK]\033[0m    \033[0;38;5;44mRemoving philo\033[0m"

re:		fclean all

.PHONY:	all clean fclean re run
