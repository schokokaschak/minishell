# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nradin <nradin@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 13:37:00 by nradin            #+#    #+#              #
#    Updated: 2023/04/04 18:58:16 by nradin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_memset.c				\
		ft_bzero.c				\
		ft_memcpy.c				\
		ft_memmove.c 			\
		ft_memchr.c				\
		ft_memcmp.c				\
		ft_isalpha.c			\
		ft_isascii.c			\
		ft_isspace.c			\
		ft_isdigit.c			\
		ft_isalnum.c			\
		ft_isprint.c			\
		ft_tolower.c			\
		ft_toupper.c			\
		ft_strchr.c				\
		ft_atoi.c				\
		ft_strlen.c				\
		ft_strlcat.c			\
		ft_strlcpy.c			\
		ft_strncmp.c			\
		ft_strnstr.c			\
		ft_strrchr.c			\
		ft_calloc.c				\
		ft_strdup.c				\
		ft_substr.c				\
		ft_strjoin.c			\
		ft_strtrim.c			\
		ft_split.c				\
		ft_itoa.c				\
		ft_strmapi.c			\
		ft_striteri.c			\
		ft_putchar_fd.c			\
		ft_putstr_fd.c			\
		ft_putendl_fd.c			\
		ft_putnbr_fd.c			\
		get_next_line.c			\
		get_next_line_utils.c	\
		ft_strnew.c 			\
		ft_strcpy.c 			\
		ft_strndup.c 			\
		ft_strcat.c 			\
		ft_strncpy.c 			\
		ft_strnchr.c			\

SRCSB =	$(SRCS)				\
		ft_lstadd_back.c	\
		ft_lstadd_front.c	\
		ft_lstclear.c		\
		ft_lstdelone.c		\
		ft_lstiter.c		\
		ft_lstlast.c		\
		ft_lstmap.c			\
		ft_lstnew.c			\
		ft_lstsize.c		\

NAME = libft.a

OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

OBJSB = $(SRCSB:.c=.o)
OBJECTS_BONUS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJSB))

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror

$(OBJS_DIR)%.o : %.c libft.h
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@echo "\033[0;35m•\033[0m\c"

$(NAME): $(OBJECTS_PREFIXED)
	@ar r -c $(NAME) $(OBJECTS_PREFIXED)

all: $(NAME)

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus: $(OBJECTS_BONUS_PREFIXED)
	@ar r $(NAME) $(OBJECTS_BONUS_PREFIXED)
	@echo "Libft Bonus Done"
