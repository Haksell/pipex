# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/13 12:42:52 by axbrisse          #+#    #+#              #
#    Updated: 2023/03/27 05:12:37 by axbrisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
BONUS := pipex_bonus
PATH_SRCS := srcs
PATH_OBJS := objs
PATH_LIBFT := libft
PATH_TESTS := tests
GARBAGE := .pytest_cache tests/__pycache__
LIBFT := libft/libft.a
INCLUDES := -I./includes -I./libft/includes
HEADER := ./includes/pipex.h
CC := cc -Wall -Wextra -Werror

FILES := heredoc init main utils
vpath %.c ${PATH_SRCS}
SRCS := ${addsuffix .c, ${FILES}}
OBJS := ${patsubst %.c, ${PATH_OBJS}/%.o, ${SRCS}}

all: ${NAME}

${OBJS}: ${PATH_OBJS}/%.o: %.c ${HEADER}
	@mkdir -p ${PATH_OBJS}
	${CC} -c $< -o $@ ${INCLUDES}

${NAME} ${BONUS}: ${LIBFT} ${OBJS}
	${CC} ${OBJS} -L${PATH_LIBFT} -lft -o $@

${LIBFT}:
	${MAKE} -s -C ${PATH_LIBFT}

clean:
	${MAKE} -s -C ${PATH_LIBFT} fclean
	rm -rf ${PATH_OBJS} ${GARBAGE}

fclean: clean
	rm -f ${NAME} ${BONUS}

re: fclean ${NAME}

bonus: ${BONUS}

test:
	@pytest -rA ${PATH_TESTS}

.PHONY: all bonus clean fclean re test
