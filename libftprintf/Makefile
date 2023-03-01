NAME	=	libftprintf.a

MAKE	=	make

SRC_DIR_LIBFT	=	./libft/

OBJ_DIR_LIBFT	=	./libft/.obj/

HDS_DIR_LIBFT	=	./libft/

LIST_SRC_LIBFT	=	ft_isalpha.c  ft_isdigit.c  ft_isalnum.c  ft_isascii.c  \
					ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
					ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
					ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
					ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
					ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
					ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
					ft_putnbr_fd.c get_next_line.c ft_strcmp.c


LIST_OBJ_LIBFT	=	$(LIST_SRC_LIBFT:.c=.o)

LIST_HDS_LIBFT	=	libft.h get_next_line.h

SRC_LIBFT		=	$(addprefix $(SRC_DIR_LIBFT), $(LIST_SRC_LIBFT))

OBJ_LIBFT		=	$(addprefix $(OBJ_DIR_LIBFT), $(LIST_OBJ_LIBFT))

HDS_LIBFT		=	$(addprefix $(HDS_DIR_LIBFT), $(LIST_HDS_LIBFT))


SRC_DIR_PRINTF	=	./

OBJ_DIR_PRINTF	=	./.obj/

HDS_DIR_PRINTF	=	./

LIST_SRC_PRINTF	=	ft_printf.c ft_print_int.c ft_print_ptr.c ft_print_unsigned.c\
					ft_utils.c

LIST_OBJ_PRINTF	=	$(LIST_SRC_PRINTF:.c=.o)

LIST_HDS_PRINTF	=	ft_printf.h

SRC_PRINTF	=	$(addprefix $(SRC_DIR_PRINTF), $(LIST_SRC_PRINTF))

OBJ_PRINTF	=	$(addprefix $(OBJ_DIR_PRINTF), $(LIST_OBJ_PRINTF))

HDS_PRINTF	=	$(addprefix $(HDS_DIR_PRINTF), $(LIST_HDS_PRINTF))


SRC		=	$(SRC_LIBFT) $(SRC_PRINTF)	

OBJ		=	$(OBJ_LIBFT) $(OBJ_PRINTF)

HDS		=	$(HDS_LIBFT) $(HDS_PRINTF)


CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

all: $(NAME)


$(NAME)	:	$(OBJ_DIR_PRINTF) $(OBJ_PRINTF) $(HDS_PRINTF) $(SRC_DIR_LIBFT)
	$(MAKE) -C libft
	ar rc $(NAME) $(OBJ_LIBFT) $(OBJ_PRINTF)
	ranlib $(NAME)


$(OBJ_DIR_PRINTF)%.o : $(SRC_DIR_PRINTF)%.c $(HDS_PRINTF)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDS_DIR_PRINTF)

$(OBJ_DIR_LIBFT)%.o : $(SRC_DIR_LIBFT)%.c $(HDS_LIBFT)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HDS_DIR_LIBFT)
	


$(OBJ_DIR_PRINTF) : 
	mkdir -p $(OBJ_DIR_PRINTF)

clean : 
	rm -rf $(OBJ_DIR_PRINTF)

fclean: clean
	rm -f $(NAME)

re:	fclean $(NAME)

.PHONY: clean fclearn re all	
