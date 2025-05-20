/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:17:09 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/20 17:37:57 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include "../lib/.mlx/mlx.h"
#include "../lib/libft/libft.h"
#include "../lib/gnl/get_next_line.h"
#include "../lib/malloc/ft_malloc.h"

#define COLOR_RESET   "\x1b[0m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_CYAN    "\x1b[36m" 
#define COLOR_RED     "\x1b[31m"




#define SKY_BOTTOM 0x87CEEB
#define FLOOR_TOP 0x696969
#define FLOOR_BOTTOM 0x36454F



 
# define WIDTH 2280
# define HEIGHT 720
# define BLOCK 1000
#define MINIMAP_WIDTH 200
#define MINIMAP_HEIGHT 200

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363


// For X11/Linux:
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307

# define PI 3.14159265359


/* ================== MINIMAP COLORS ================== */
#define WALL_COLOR 0x000000
#define PLAYER_COLOR 0x00FF00
#define RAY_COLOR 0xF7FF00
#define EMPTY_SPACE 0x1A1A2E

/* ================== 3D VIEW COLORS ================== */
#define SKY_COLOR 0x87CEEB
#define FLOOR_COLOR 0x36454F
#define WALL_TOP_COLOR 0x6B8E23
#define WALL_BOTTOM_COLOR 0x98FB98






#define MAP_WIDTH 40
#define MAP_HEIGHT 40
#define BLOCK_SIZE 10
#define PLAYER_SIZE 5



typedef struct s_map
{
	char **map;
	int width;
	int height;
} t_map;

typedef struct s_lines
{
	char            *val;
	struct s_lines  *next;
}   t_lines;

typedef struct s_img
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int		width;
	int		height;
} t_img;

typedef struct s_texture
{
	int 	no;
	int 	so;
	int 	we;
	int 	ea;
	int 	fn;
	int 	cn;
	char    *no_path;
	char    *so_path;
	char    *we_path;
	char    *ea_path;
	char    *floor_clr;
	char    *sky_clr;
	int     floor_grb[3];
	int     sky_grb[3];
	t_img *weapon;
	t_img   no_img;
	t_img   so_img;
	t_img   we_img;
	t_img   ea_img;
}   t_texture;

typedef struct s_data
{
	void *mlx;
	void *win;
	t_img img;
	t_map map;
	t_lines     *lines;
}   t_data;

typedef struct s_player
{
	float	x;
	float	y;
	float angle;

	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;

	bool left_rotate;
	bool right_rotate;
}   t_player;


#define MAX_WEAPONS 3
#define MAX_ANIM_FRAMES 3
typedef struct s_cub
{
	int		screen_h;
	int		screen_w;
	t_data data;
	t_player player;
	t_texture   *texture;
	int num_textures;
	    // ... your other members ...
   	t_img weapon[MAX_WEAPONS][MAX_ANIM_FRAMES];
    int current_weapon_index;
    int weapon_anim_frame;    // optional for animation
    // ... 
	    int weapon_anim_active; // 1 if animating
    int weapon_anim_tick;   
} t_cub;


typedef struct s_weapon_anim {
    int animating;        // flag: 0 = idle, 1 = playing
    int frame_index;      // current frame in animation
    int total_frames;     // total number of frames
    int frame_delay;      // number of game ticks to wait
    int frame_timer;      // ticks left until next frame
} t_weapon_anim;



int 	map_parsing(int ac, char **av, t_cub *cub);
int 	init_map(t_cub *cub, char *filename);
char	*read_map(int fd);
int		check_file_extention(char *str);
t_lines	*new_line(char *val);
int		check_map(t_cub *cub);
void	ft_add_line(t_lines **head, t_lines *new);
int		valid_chars(char c);
int		only_walls(char *line);
int		parse_lines(t_cub *cub);
t_lines	*textures_extracter(t_lines *line, t_texture *textur);
int		get_map_len(t_lines *line);
t_lines	*map_extracter(t_lines *line, char ***map);
int		extractor(t_cub *cub);
int		check_file_ext(char *name);
int		check_file(char *filename);
int		check_texture(t_cub *cub);
int		check_comas(char *clr1, char *clr2);
void	reset_texture(t_texture *textur);


int		init_window(t_cub *cub);
int		event_hook_window(t_cub *cub);
int		init_image(t_cub *cub);
void	initialize_player(t_player *player, t_cub *cub);
int key_release(int key, t_cub *cub);
int key_press(int key, t_cub *cub);
int close_window(t_cub *cub);
void handle_movement(t_cub *cub);
bool touch_one(float px, float py, t_cub *cub);
float use_distance(float x, float y);
float use_fixed_dist(float x1, float y1, float x2, float y2, t_cub *game);
float world_to_minimap_x(float x);
float world_to_minimap_y(float y);
void my_pixel_put(int x, int y, t_img *img, int color);
void clear_image(t_cub *cub);
void render_draw_square(int x, int y, int size, int color, t_cub *cub);
void render_draw_minimap(t_cub *cub);
void cast_ray(t_cub *cub, float start_x, int i);
int game_loop(t_cub *cub);
int mouse_move(int x, int y, t_cub *cub);
int mouse_scroll(int button, int x, int y, t_cub *cub);






#endif