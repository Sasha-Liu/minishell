# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sasha <sasha@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/26 11:49:10 by hsliu             #+#    #+#              #
#    Updated: 2023/03/01 12:41:30 by sasha            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

MAKE	=	make

SRC_DIR	=	./src/

OBJ_DIR	=	./.obj/

INC_DIR	=	./include/

VPATH	=	./src/parsing ./src/exec ./src/builtin ./src/signal ./src/minishell

LIST_MINISHELL	=	ft_get_env.c token_utils.c \

LIST_PARSING	=	line_to_token_utils.c ft_line_to_token.c  \
					dollar_exp_utils.c ft_dollar_exps.c \
					ft_get_homedir.c tilde_exps_utils.c ft_tilde_exps.c \
					ft_exps_and_split.c ft_field_split.c ft_rm_quote.c \
					parsing.c ft_set_pipe.c ft_get_cmd.c \
					test.c

LIST_EXEC		= ft_get_cmd.c ft_exec_builtin.c exec.c ft_file_descriptor.c ft_files.c \
					ft_get_path_cmd.c ft_here_doc.c ft_free.c exec_pipe.c loop.c

LIST_BUILTIN	= ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c 

LIST_SIGNAL		=

MINISHELL_DIR	=	$(addprefix $(SRC_DIR), minishell)

PARSING_DIR		=	$(addprefix $(SRC_DIR), parsing)

EXEC_DIR		=	$(addprefix $(SRC_DIR), exec)

BUILTIN_DIR		=	$(addprefix $(SRC_DIR), builtin)

SIGNAL_DIR		=	$(addprefix $(SRC_DIR), signal)

SRC		=	$(addprefix $(MINISHELL_DIR), $(LIST_MINISHELL)) \
			$(addprefix $(PARSING_DIR), $(LIST_PARSING)) \
			$(addprefix $(EXEC_DIR), $(LIST_EXEC)) \
			$(addprefix $(BUILTIN_DIR), $(LIST_BUILTIN)) \
			$(addprefix $(SIGNAL_DIR), $(LIST_SIGNAL))

OBJ		=	$(addprefix $(OBJ_DIR), $(LIST_MINISHELL:.c=.o)) \
			$(addprefix $(OBJ_DIR), $(LIST_PARSING:.c=.o)) \
			$(addprefix $(OBJ_DIR), $(LIST_EXEC:.c=.o)) \
			$(addprefix $(OBJ_DIR), $(LIST_BUILTIN:.c=.o)) \
			$(addprefix $(OBJ_DIR), $(LIST_SIGNAL:.c=.o))

LIST_INC	=	minishell.h parsing.h exec.h builtin.h

INC		=	$(addprefix $(INC_DIR), $(LIST_INC))

LIB_DIR	=	libftprintf

LIB		=	libftprintf/libftprintf.a

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

all: $(NAME)

$(NAME)	:	$(OBJ_DIR) $(OBJ) $(INC) $(LIB) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) -lreadline

$(LIB): $(LIB_DIR)
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR)%.o : %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) 

$(OBJ_DIR) : 
	mkdir -p $(OBJ_DIR)

clean : 
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re:	fclean $(NAME)

.PHONY: clean fclearn re all
