# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 19:18:15 by sarchoi           #+#    #+#              #
#    Updated: 2022/02/28 22:01:51 by sarchoi          ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)
SRCS_BONUS = $(wildcard src/*_bonus.c)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

INC_FLAGS = -I includes

green:=$(shell tput setaf 2)
reset:=$(shell tput sgr0)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lpthread
	$(info $(green)<MAKE> NAME$(reset))

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)
	$(info $(green)<MAKE> $(<) -> $(@)$(reset))

bonus: $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $@ $(OBJS_BONUS)
	$(info $(green)<MAKE> bonus$(reset))

clean:
	@rm -f $(OBJS)
	$(info $(green)<MAKE> clean$(reset))

fclean: clean
	@rm -f $(NAME)
	$(info $(green)<MAKE> fclean$(reset))

re: fclean all
	$(info $(red)<MAKE> re$(reset))

.PHONY: all clean fclean re
