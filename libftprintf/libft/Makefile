
NAME	=	libft.a

SRC_DIR	=	./

OBJ_DIR	=	./.obj/

HD_DIR	=	./

LIST_SRC	=	ft_isalpha.c  ft_isdigit.c  ft_isalnum.c  ft_isascii.c  ft_isprint.c ft_strlen.c \
				ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c \
				ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
				ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
				ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c ft_calloc.c get_next_line.c ft_strcmp.c

LIST_OBJ	=	$(LIST_SRC:.c=.o)

LIST_HDS	=	libft.h get_next_line.h

LIST_BONUS_SRC	=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
					ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
					ft_lstmap_bonus.c

LIST_BONUS_OBJ	=	$(LIST_BONUS_SRC:.c=.o)

SRC		=	$(addprefix $(SRC_DIR), $(LIST_SRC))

OBJ		=	$(addprefix $(OBJ_DIR), $(LIST_OBJ))

HDS		=	$(addprefix $(HD_DIR), $(LIST_HDS))

BONUS_SRC	=	$(addprefix $(SRC_DIR), $(LIST_BONUS_SRC))

BONUS_OBJ	=	$(addprefix $(OBJ_DIR), $(LIST_BONUS_OBJ))

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME)	:	$(OBJ_DIR) $(OBJ) $(HDS)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HDS)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HD_DIR)

$(OBJ_DIR) : 
	mkdir -p $(OBJ_DIR)

bonus : $(OBJ_DIR) $(OBJ) $(BONUS_OBJ) $(HDS)
	ar rc $(NAME) $(OBJ) $(BONUS_OBJ)
	ranlib $(NAME)

clean : 
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re:	fclean $(NAME)

.PHONY: clean fclearn re all	

