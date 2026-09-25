NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
SRC			= ft_char.c ft_str.c ft_mem.c ft_putfd.c ft_split.c \
			  ft_strtrim.c ft_convert.c
OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: %.c libft.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
