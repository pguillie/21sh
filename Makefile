# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/09 12:40:11 by pguillie          #+#    #+#              #
#    Updated: 2017/07/23 18:08:59 by pguillie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 42sh
CC		= gcc
FLAGS	= -Wall -Werror -Wextra
INCPATH	= includes/
HEADERS	= $(addprefix $(INCPATH), shell.h snake.h)
LIBPATH	= libft/
LIB		= $(LIBPATH)libft.a
TERMCAP	= -ltermcap

SOURCES	:= $(shell find src | grep "\.c" | grep -v "\.c.")
NB		:= $(shell find src | grep "\.c" | grep -v "\.c." | wc -l\
		| rev | cut -f 1 -d ' ' | rev)

OBJECTS	= $(SOURCES:src/%.c=obj/%.o)

RED		= \033[31m
GREEN	= \033[32m
BLUE	= \033[34m
WHITE	= \033[37m
EOC		= \033[0m

.PHONY: all clean nclean fclean re

all: $(NAME)

$(NAME): obj $(LIB) $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LIB) $(TERMCAP)
	@ echo "$(GREEN)[$@]: binary successfully created !$(EOC)"

obj/%.o: src/%.c $(HEADERS)
	$(eval FILE=$(shell echo $$(($(FILE) + 1))))
	$(eval PERCENT=$(shell echo $$(($(FILE) * 100 / $(NB)))))
	@ echo "[$(NAME)]: $(PERCENT)% ($(FILE)/$(NB))\r\c"
	$(CC) $(FLAGS) -I $(INCPATH) -o $@ -c $<

obj:
	mkdir -p ./obj
	@ echo "$(BLUE)[$(NAME)]: objects directory created$(EOC)"

$(LIB):
	make -C $(LIBPATH)

clean:
	make -C $(LIBPATH) clean
	rm -rf obj
	@ echo "$(RED)[$(NAME)]: objects directory deleted$(EOC)"

nclean:
	rm -rf $(NAME)
	@ echo "$(RED)[$(NAME)]: binary file deleted$(EOC)"

fclean: clean nclean
	make -C $(LIBPATH) nclean

re: fclean all
