MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
SRCS = ./src/main.c
OBJS = $(SRCS:.c=.o)
NAME = cub3d

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS)

clean:
	@$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
