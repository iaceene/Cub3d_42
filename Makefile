# Directories
MLX_DIR		= ./bonus/src/lib/.mlx
MLX_LIB		= $(MLX_DIR)/libmlx.a
LIBFT_DIR	= ./bonus/src/lib/libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a
SRC_DIR		= ./bonus/src
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lbsd

SRCS		= \
			$(SRC_DIR)/lib/gnl/get_next_line.c \
			$(SRC_DIR)/lib/gnl/get_next_line_utils.c \
			$(SRC_DIR)/lib/malloc/ft_malloc.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile_bonus.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile_2_bonus.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile_3_bonus.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile_4_bonus.c \
			$(SRC_DIR)/components/parsing/map_parsing_utile_5_bonus.c \
			$(SRC_DIR)/components/parsing/map_parsing_bonus.c \
			$(SRC_DIR)/components/rendring/core/init_bonus.c \
        	$(SRC_DIR)/components/rendring/player/controls_bonus.c \
        	$(SRC_DIR)/components/rendring/player/movement_bonus.c \
        	$(SRC_DIR)/components/rendring/utils/map_utils_bonus.c \
        	$(SRC_DIR)/components/rendring/graphics_bonus.c \
			$(SRC_DIR)/components/rendring/utils_rycaster_bonus.c \
        	$(SRC_DIR)/components/rendring/minimap/utils_one_minimap_bonus.c \
        	$(SRC_DIR)/components/rendring/minimap/utils_two_minimap_bonus.c \
        	$(SRC_DIR)/components/rendring/minimap/minimap_bonus.c \
        	$(SRC_DIR)/components/rendring/raycaster_bonus.c \
        	$(SRC_DIR)/components/rendring/floor_sky/floor_sky_bonus.c \
        	$(SRC_DIR)/components/rendring/weapon/weapon_bonus.c \
        	$(SRC_DIR)/components/rendring/wall/wall_bonus.c \
        	$(SRC_DIR)/components/rendring/weapon/init_weapon_bonus.c \
			$(SRC_DIR)/main/main_bonus.c \

OBJS = $(SRCS:.c=.o)

NAME = cub3D

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB):
	@$(MAKE) -s -C $(MLX_DIR)

$(LIBFT_LIB):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) ./bonus/src/include/cub3d.h
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
