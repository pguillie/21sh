# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MakeFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguillie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/01 11:10:37 by pguillie          #+#    #+#              #
#*   Updated: 2017/10/26 16:09:18 by pbourlet         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= gcc
FLAGS	= -Wall -Werror -Wextra
INCPATH	= includes/
HEADERS	= $(addprefix $(INCPATH),\
		  libft.h ft_printf.h get_next_line.h error_msg.h)

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

$(NAME): obj $(OBJECTS)
	ar rc $@ $(OBJECTS)
	ranlib $@
	@ echo "$(GREEN)[$@]: archive successfully created !$(EOC)"

obj/%.o: src/%.c $(HEADERS)
	$(eval FILE=$(shell echo $$(($(FILE) + 1))))
	$(eval PERCENT=$(shell echo $$(($(FILE) * 100 / $(NB)))))
	@ echo "[$(NAME)]: $(PERCENT)% ($(FILE)/$(NB))\r\c"
	$(CC) $(FLAGS) -I $(INCPATH) -o $@ -c $<

obj:
	mkdir -p ./obj/libft
	mkdir -p ./obj/ft_printf
	mkdir -p ./obj/get_next_line
	@ echo "$(BLUE)[$(NAME)]: objects directory created$(EOC)"

clean:
	rm -rf obj
	@ echo "$(RED)[$(NAME)]: objects directory deleted$(EOC)" 

nclean:
	rm -rf $(NAME)
	@ echo "$(RED)[$(NAME)]: archive library deleted$(EOC)"

fclean: clean nclean

re : fclean all
