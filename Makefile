MLX_DIR = ./src/lib/.mlx
MLX_LIB = $(MLX_DIR)/libmlx.a

LIBFT_DIR = ./src/lib/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lbsd

SRCS =	./src/lib/gnl/get_next_line.c\
		./src/lib/gnl/get_next_line_utils.c\
		./src/lib/malloc/ft_malloc.c\
		./src/components/parsing/map_parsing_utile.c\
        ./src/components/parsing/map_parsing_utile_2.c\
        ./src/components/parsing/map_parsing_utile_3.c\
		./src/components/parsing/map_parsing.c\
		./src/main/main.c
OBJS = $(SRCS:.c=.o)
NAME = cub3D


all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS)

clean:
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
