NAME		= miniRT

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

INC_DIRS	= -Iinclude -Ilibft -Iminilibx-linux
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx_Linux.a
LDFLAGS		= -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux \
			  -lXext -lX11 -lm

SRC			= src/main.c \
			  src/parser/parser_file.c \
			  src/parser/parser_number.c \
			  src/parser/parser_vector.c \
			  src/parser/parser_elements.c \
			  src/parser/parser_objects.c \
			  src/parser/parser_core.c \
			  src/parser/parser_free.c \
			  src/math/vector.c \
			  src/math/vector2.c \
			  src/render/intersect_sphere.c \
			  src/render/intersect_plane.c \
			  src/render/intersect_cylinder.c \
			  src/render/scene_hit.c \
			  src/render/camera.c \
			  src/render/color.c \
			  src/render/lighting.c \
			  src/render/render.c \
			  src/hooks/mlx_utils.c \
			  src/hooks/hooks.c \
			  src/hooks/display.c \
			  src/utils/error.c \
			  src/utils/export.c

OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: %.c include/minirt.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

bonus: all

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	-$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
