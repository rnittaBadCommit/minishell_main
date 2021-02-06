# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 22:19:56 by syudai            #+#    #+#              #
#    Updated: 2021/02/04 23:06:04 by syudai           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c\
	   ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c\
	   ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c\
	   ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
	   ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c\
	   ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	   ft_strcmp.c ft_strcpy.c
B_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
	     ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
		 ft_lstiter.c ft_lstmap.c
OBJS = $(SRCS:%.c=%.o)
B_OBJS = $(B_SRCS:%.c=%.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I libft/ -I includes/
SANI = -fsanitize=address
LEAK = -fsanitize=leak
SRCS = pipe/pipe.c pipe/is_x.c pipe/utils_a.c pipe/main.c builtins/cd.c\
		builtins/echo.c builtins/export.c builtins/pwd.c builtins/unset.c \
		builtins/env.c read_command.c get_exec_path.c utils.c argument.c\
		main.c quotes.c make_strb.c syntax_check.c builtins/exit.c pipe/utils_b.c\
		utils_c.c quote.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

bonus: $(OBJS) $(B_OBJS)
	ar rc $(NAME) $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME) bonus

clean:
	rm -f $(OBJS)
	rm -f $(B_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
