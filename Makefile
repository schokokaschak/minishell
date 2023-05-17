# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 09:48:23 by nradin            #+#    #+#              #
#    Updated: 2023/04/02 21:33:04 by akashets         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c						\
		signals.c					\
		sig_handle.c				\
		lexer.c						\
		lexer_utils.c				\
		lexer_tokens.c				\
		free.c						\
		parse.c						\
		lexical_errors.c			\
		lexical_errors_utils.c		\
		checkers.c					\
		checkers_2.c				\
		parse_recursion_depth.c		\
		parse_log_group.c			\
		parse_pipe_group.c			\
		parse_command.c				\
		envp.c						\
		parse_extensions.c			\
		wildcards.c					\
		wildcards_utils.c			\
		wildcards_str_list.c		\
		parse_command_fd.c			\
		parse_command_here_doc.c	\
		parse_command_utils.c		\
		builtins.c					\
		builtin_echo.c				\
		builtin_unset.c				\
		builtin_pwd.c				\
		builtin_exit.c				\
		builtin_export.c			\
		builtin_cd.c				\
		execution_log.c 			\
		execution_pipes.c			\
		execution_utils.c 			\
		execution_cmnds.c 			\
		parse_command_get_cmnd.c 	\
 
NAME = minishell

LIBFT = include/libft/
SRCS_DIR = src/

OBJS_DIR = objs/
OBJS = $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror -g -fcommon

all: $(NAME) $(BONUS)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c include/minishell.h
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CC_FLAGS) -O3 -c $< -o $@
	@echo "\033[0;35m•\033[0m\c"

$(NAME): $(OBJECTS_PREFIXED)
	@make -C $(LIBFT)
	@$(CC) -g -o $(NAME) $(OBJECTS_PREFIXED) $(LIBFT)libft.a -lreadline
	@echo "\n\033[0;35m✨minishell successfully compiled!✨"

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_BONUS_DIR)
	@make fclean -C $(LIBFT)
	@echo "\033[0;34m✨minishell successfully cleaned!✨\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(BONUS)

re: fclean all
