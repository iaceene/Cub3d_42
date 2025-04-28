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

typedef struct s_data
{
    void *mlx;
    void *win;
    t_img img;
    t_map map;
    t_player player;
} t_data;

typedef struct s_texture
{
    char *path;
    int width;
    int height;
    unsigned int *data;
} t_texture;

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
    t_texture textures[4];
    int num_textures;
} t_cub;

int map_parsing(int ac, char **av, t_cub *cub);
int init_map(t_cub *cub, char *filename);
int init_player(t_cub *cub);
int init_textures(t_cub *cub);
int init_window(t_cub *cub);
int init_mlx(t_cub *cub);
int init_img(t_cub *cub);


#endif