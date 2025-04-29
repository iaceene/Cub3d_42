#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include "../lib/.mlx/mlx.h"
#include "../lib/libft/libft.h"
#include "../lib/gnl/get_next_line.h"
#include "../lib/malloc/ft_malloc.h"

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


typedef struct s_player
{
	double x;
	double y;
	double angle;
} t_player;

typedef struct s_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img;

typedef struct s_texture
{
	char    *no_path;
	char    *so_path;
	char    *we_path;
	char    *ea_path;
	char    *floor_clr;
	char    *sky_clr;
	int     floor_grb[3];
	int     sky_grb[3];
}   t_texture;

typedef struct s_data
{
	void *mlx;
	void *win;
	t_img img;
	t_map map;
	t_lines     *lines;
	t_player    player;
}   t_data;

typedef struct s_ray
{
	double angle;
	double distance;
	int hit_x;
	int hit_y;
} t_ray;

typedef struct s_cub
{
	t_data data;
	t_texture   *texture;
	int num_textures;
} t_cub;

int 	map_parsing(int ac, char **av, t_cub *cub);
int 	init_map(t_cub *cub, char *filename);
char	*read_map(int fd);
int		check_file_extention(char *str);
int		init_map(t_cub *cub, char *filename);
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


#endif