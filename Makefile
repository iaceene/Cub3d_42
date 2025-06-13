# Directories
MLX_DIR		= ./src/lib/.mlx
MLX_LIB		= $(MLX_DIR)/libmlx.a
LIBFT_DIR	= ./src/lib/libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a
SRC_DIR		= ./src
CC			= cc
<<<<<<< HEAD
CFLAGS		=  -g3 
=======
CFLAGS		= -Wall -Wextra -Werror #-g3 -fsanitize=address
>>>>>>> cub3D_v3
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lbsd

SRCS		= \
			$(SRC_DIR)/lib/gnl/get_next_line.c \
			$(SRC_DIR)/lib/gnl/get_next_line_utils.c \
			$(SRC_DIR)/lib/malloc/ft_malloc.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile.c \
			$(SRC_DIR)/components/parsing/parsing_errors.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile_2.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile_3.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile_4.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile_5.c \
			$(SRC_DIR)/components/parsing/map_parsing.c \
<<<<<<< HEAD
			$(SRC_DIR)/components/rendring/init_window.c \
			$(SRC_DIR)/main/main.c
=======
			$(SRC_DIR)/components/rendring/core/init.c \
        	$(SRC_DIR)/components/rendring/player/controls.c \
        	$(SRC_DIR)/components/rendring/player/movement.c \
        	$(SRC_DIR)/components/rendring/utils/map_utils.c \
        	$(SRC_DIR)/components/rendring/graphics.c \
			$(SRC_DIR)/components/rendring/utils_rycaster.c \
        	$(SRC_DIR)/components/rendring/minimap/utils_one_minimap.c \
        	$(SRC_DIR)/components/rendring/minimap/utils_two_minimap.c \
        	$(SRC_DIR)/components/rendring/minimap/minimap.c \
        	$(SRC_DIR)/components/rendring/raycaster.c \
        	$(SRC_DIR)/components/rendring/floor_sky/floor_sky.c \
        	$(SRC_DIR)/components/rendring/weapon/weapon.c \
        	$(SRC_DIR)/components/rendring/wall/wall.c \
        	$(SRC_DIR)/components/rendring/weapon/init_weapon.c \
			$(SRC_DIR)/main/main.c \
>>>>>>> cub3D_v3

OBJS = $(SRCS:.c=.o)

NAME = cub3D

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB):
	@$(MAKE) -s -C $(MLX_DIR)

$(LIBFT_LIB):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) ./src/include/cub3d.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_FLAGS)
	@echo "$(NAME) compiled successfully"

clean:
	@$(MAKE) -s -C $(MLX_DIR) clean
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@echo "Object files removed"

fclean: clean
	@$(MAKE) -s -C $(MLX_DIR) clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(NAME) removed"

re: fclean all

.PHONY: all clean fclean re
