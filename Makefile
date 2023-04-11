# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchapuis <pchapuis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/26 11:49:10 by hsliu             #+#    #+#              #
#    Updated: 2023/04/11 14:09:39 by pchapuis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

MAKE	=	make

SRC_DIR	=	./src/

OBJ_DIR	=	./.obj/

INC_DIR	=	./include/

VPATH	=	./src/parsing ./src/exec ./src/builtin ./src/signal ./src/minishell

LIST_MINISHELL	=	ft_init_shell.c token_utils.c \

LIST_PARSING	=	line_to_token_utils.c ft_line_to_token.c  \
					dollar_exp_utils.c ft_dollar_exps.c \
					ft_get_homedir.c tilde_exps_utils.c ft_tilde_exps.c \
					ft_exps_and_split.c ft_field_split.c ft_rm_quote.c \
					parsing.c ft_set_pipe.c ft_get_cmd.c ft_init_command.c ft_redirect.c\
					ft_here_doc.c ft_exit_status_exp.c\

LIST_EXEC		=	main.c \
					exec.c \
					get_path.c \
					get_path_utils.c \
					launch.c \
					close.c \
					error.c \
					builtin.c \
					signal.c \
					signal_handle.c \
					wait.c

LIST_BUILTIN	=	ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c env_utils.c

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

CFLAGS	=	-Wall -Wextra -Werror

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
