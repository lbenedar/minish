# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbenedar <lbenedar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 18:43:09 by lbenedar          #+#    #+#              #
#    Updated: 2021/09/20 14:32:28 by lbenedar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell

SRCS_DIR 	=	srcs

GNL_DIR		=	$(SRCS_DIR)/gnl

LIB_DIR		=	$(SRCS_DIR)/libft

EXEC_DIR	=	$(SRCS_DIR)/exec

PARSER_DIR	=	$(SRCS_DIR)/parser

SIGNAL_DIR	=	$(SRCS_DIR)/signal_handler

SRCS		=	$(SRCS_DIR)/main.c \
				$(SRCS_DIR)/minishell.c \
				$(SRCS_DIR)/draw_shell.c \
				$(SRCS_DIR)/read_content.c \
				$(SRCS_DIR)/check_string.c \
				$(SRCS_DIR)/pipe_utils.c \
				$(SRCS_DIR)/out_error.c \
				$(SRCS_DIR)/sigint_handler.c \
				$(SRCS_DIR)/setup_redirect.c \
				$(SRCS_DIR)/env_utils.c \
				$(SRCS_DIR)/set_env.c \
				$(SRCS_DIR)/ft_free.c \
				$(SRCS_DIR)/find_command.c \
				$(SRCS_DIR)/exec_command.c \
				$(EXEC_DIR)/exec_cd.c \
				$(EXEC_DIR)/exec_pwd.c \
				$(EXEC_DIR)/exec_export.c \
				$(EXEC_DIR)/exec_exit.c \
				$(EXEC_DIR)/exec_file.c \
				$(EXEC_DIR)/exec_echo.c \
				$(EXEC_DIR)/exec_env.c \
				$(EXEC_DIR)/exec_unset.c \
				$(GNL_DIR)/get_next_line.c \
				$(GNL_DIR)/get_next_line_utils.c \
				$(LIB_DIR)/ft_strcpy.c \
				$(LIB_DIR)/ft_strdup.c \
				$(LIB_DIR)/ft_strlcpy.c \
				$(LIB_DIR)/ft_putstr.c \
				$(LIB_DIR)/ft_putchar_fd.c \
				$(LIB_DIR)/ft_strndup.c \
				$(LIB_DIR)/ft_strljoin.c \
				$(LIB_DIR)/ft_strjoin.c \
				$(LIB_DIR)/ft_memcpy.c \
				$(LIB_DIR)/ft_split.c \
				$(LIB_DIR)/ft_calloc.c \
				$(LIB_DIR)/ft_bzero.c \
				$(LIB_DIR)/ft_memcmp.c \
				$(LIB_DIR)/ft_strlen.c \
				$(LIB_DIR)/ft_replace.c \
				$(LIB_DIR)/ft_strnstr.c \
				$(LIB_DIR)/ft_strcmp.c \
				$(LIB_DIR)/ft_strchr.c \
				$(LIB_DIR)/ft_split_one.c \
				$(LIB_DIR)/ft_atoi.c \
				$(PARSER_DIR)/check_str.c \
				$(PARSER_DIR)/ft_get_data.c \
				$(PARSER_DIR)/ft_get_redirect.c \
				$(PARSER_DIR)/ft_split_cmds_utils.c \
				$(PARSER_DIR)/ft_split_cmds.c \
				$(PARSER_DIR)/ft_str_woq_utils.c \
				$(PARSER_DIR)/ft_str_woq.c \
				$(PARSER_DIR)/parser_utils.c \
				$(PARSER_DIR)/parser.c
				

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wextra -Werror -Wall -ggdb3

OPTFLAGS	=	-O2

LFLAGS		=	-lreadline

INC_DIR		=	includes

INC			=	-I$(INC_DIR)

RM			=	rm -f

CC			=	gcc

NORM		=	norminette

NORM_PATHS	=	$(SRCS_DIR)/*.c \
				$(GNL_DIR)/*.c \
				$(LIB_DIR)/*.c \
				$(EXEC_DIR)/*.c \
				$(PARSER_DIR)/*.c \
				$(INC_DIR)/*.h

all:
	$(MAKE) $(NAME) -j 4

bonus: all

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OPTFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

norm:
	$(NORM) $(NORM_PATHS)

re: fclean all

%.o:%.c
	$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@ $(INC) $(LFLAGS)

.PHONY: all bonus clean fclean re

