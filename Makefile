# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 12:42:52 by axbrisse          #+#    #+#              #
#    Updated: 2023/02/19 07:28:54 by axbrisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
BONUS := pipex_bonus

PATH_SRCS := srcs
PATH_OBJS := objs
PATH_LIBFT := libft
PATH_TESTS := tests
LIBFT := libft/libft.a
INCLUDES := -I./includes -I./libft/includes
HEADER := ./includes/pipex.h

FILES := check_args main path pipes

vpath %.c ${PATH_SRCS}

SRCS = ${addsuffix .c, ${FILES}}
OBJS = ${patsubst %.c, ${PATH_OBJS}/%.o, ${SRCS}}

CC = cc -Wall -Wextra -Werror

all: ${NAME}

${OBJS}: ${PATH_OBJS}/%.o: %.c ${HEADER}
	@mkdir -p ${PATH_OBJS}
	${CC} -c $< -o $@ ${INCLUDES}

${NAME} ${BONUS}: ${LIBFT} ${OBJS}
	${CC} ${OBJS} -L${PATH_LIBFT} -lft -o $@

${LIBFT}:
	${MAKE} -s -C ${PATH_LIBFT}

clean:
	${MAKE} -s -C ${PATH_LIBFT} clean
	rm -rf ${PATH_OBJS} .pytest_cache

fclean: clean
	${MAKE} -s -C ${PATH_LIBFT} fclean
	rm -f ${NAME} ${BONUS}

re: fclean ${NAME}

bonus: ${BONUS}

.PHONY: all bonus clean fclean re
