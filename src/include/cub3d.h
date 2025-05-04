/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:17:09 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/04 17:13:01 by yaajagro         ###   ########.fr       */
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
	int	x;
	int	y;
}   t_player;

typedef struct s_cub
{
	int		screen_h;
	int		screen_w;
	t_data data;
	t_player player;
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
int		check_comas(char *clr1, char *clr2);
void	reset_texture(t_texture *textur);
int		valid_chars(char c);
int		get_map_len(t_lines *line);
int		init_window(t_cub *cub);
void	render_map(t_cub *cub);
void	draw_player(t_img *img, int xp, int yp, int color);
void	my_pixel_put(int x, int y, t_img *img, int color);

#endif