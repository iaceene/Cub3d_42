# Directories
MLX_DIR		= ./mlx
MLX_LIB		= $(MLX_DIR)/libmlx.a
SRC_DIR		= ./src
OBJ_DIR		= ./obj
CC			= cc
CFLAGS		= -g3 -fsanitize=address
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lbsd

SRCS		= $(SRC_DIR)/main/main.c


OBJS		= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

NAME		= cub3D

all: $(MLX_LIB) $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/main

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB):
	@$(MAKE) -s -C $(MLX_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS)
	@echo "$(NAME) compiled successfully"

clean:
	@$(MAKE) -s -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@rm -f $(NAME)
	@echo "$(NAME) removed"

re: fclean all

.PHONY: all clean fclean re
