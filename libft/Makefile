# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 22:24:32 by axbrisse          #+#    #+#              #
#    Updated: 2023/02/09 20:46:25 by axbrisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft
LIBRARY := ${addsuffix .a, ${NAME}}
SHARED_LIBRARY := ${addsuffix .so, ${NAME}}

PATH_SRCS += srcs/conversion
PATH_SRCS += srcs/chars
PATH_SRCS += srcs/clean
PATH_SRCS += srcs/dynamic_strings
PATH_SRCS += srcs/ft_split
PATH_SRCS += srcs/get_next_line
PATH_SRCS += srcs/linked_lists
PATH_SRCS += srcs/math
PATH_SRCS += srcs/memory
PATH_SRCS += srcs/output
PATH_SRCS += srcs/strings

FILES += ft_atoi
FILES += ft_atoi_safe
FILES += ft_bzero
FILES += ft_calloc
FILES += ft_close
FILES += ft_ds_append
FILES += ft_ds_extend
FILES += ft_ds_new
FILES += ft_endswith
FILES += ft_free
FILES += ft_free_double_pointer
FILES += ft_isalnum
FILES += ft_isalpha
FILES += ft_isascii
FILES += ft_isdigit
FILES += ft_islower
FILES += ft_isprint
FILES += ft_isspace
FILES += ft_isupper
FILES += ft_itoa
FILES += ft_lstadd_back
FILES += ft_lstadd_front
FILES += ft_lstclear
FILES += ft_lstdelone
FILES += ft_lstiter
FILES += ft_lstlast
FILES += ft_lstmap
FILES += ft_lstnew
FILES += ft_lstsize
FILES += ft_lst_get
FILES += ft_lst_includes
FILES += ft_lst_sort
FILES += ft_memchr
FILES += ft_memcmp
FILES += ft_memcpy
FILES += ft_memmove
FILES += ft_memset
FILES += ft_num_words
FILES += ft_printf
FILES += ft_putbase_fd
FILES += ft_putchar_fd
FILES += ft_putendl_fd
FILES += ft_putnbr_fd
FILES += ft_putstr_fd
FILES += ft_split
FILES += ft_split_set
FILES += ft_startswith
FILES += ft_strchr
FILES += ft_strcmp
FILES += ft_strdup
FILES += ft_striteri
FILES += ft_strjoin
FILES += ft_strjoin3
FILES += ft_strlcat
FILES += ft_strlcpy
FILES += ft_strlen
FILES += ft_strmapi
FILES += ft_strncmp
FILES += ft_strnstr
FILES += ft_strrchr
FILES += ft_strtrim
FILES += ft_substr
FILES += ft_tolower
FILES += ft_toupper
FILES += get_next_line

SRCS := ${addsuffix .c, ${FILES}}

INCLUDES := includes
HEADER := includes/libft.h

vpath %.c ${PATH_SRCS}

PATH_OBJS := objs
OBJS := ${patsubst %.c, ${PATH_OBJS}/%.o, ${SRCS}}

AR := ar rcs
CC := cc
CFLAGS := -Wall -Wextra -Werror

all: ${LIBRARY}

${LIBRARY}: ${OBJS}
	${AR} ${LIBRARY} $^

${OBJS}: ${PATH_OBJS}/%.o: %.c ${HEADER}
	@mkdir -p ${PATH_OBJS}
	${CC} ${CFLAGS} -fPIC -c $< -o $@ -I${INCLUDES}

clean:
	rm -rf ${PATH_OBJS}

fclean: clean
	rm -f ${LIBRARY}
	rm -f ${SHARED_LIBRARY}
	rm -rf .pytest_cache
	rm -rf tests/__pycache__

re: fclean ${LIBRARY}

pretest: ${OBJS}
	@${CC} -fPIC -shared -o ${SHARED_LIBRARY} ${OBJS}

test: pretest
	pytest -rA -vv tests

retest: fclean test

.PHONY: all clean fclean re pretest test retest
