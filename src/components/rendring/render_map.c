/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:14:22 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/10 03:32:05 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void my_pixel_put(int x, int y, t_img *img, int color)
{
	int offset;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)(img->addr + offset) = color;
}

void fill_tile(t_img *img, int clr, int y, int x)
{
	int hight;
	int width;

	hight = 0;
	while (hight < TILE_SIZE)
	{
		width = 0;
		while (width < TILE_SIZE)
		{
			my_pixel_put(x * TILE_SIZE + width, y * TILE_SIZE + hight, img, clr);
			width++;
		}
		hight++;
	}
}

double deg_to_rad(double deg)
{
	return (deg * PI / 180.0);
}

void draw_player(t_img *img, t_player point, int color)
{
	my_pixel_put(point.x * TILE_SIZE + point.x_bit, point.y * TILE_SIZE + point.y_bit, img, 0xFFFF00);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

int init_image(t_cub *cub)
{
	cub->data.img.img = mlx_new_image(cub->data.mlx, TILE_SIZE * 21, TILE_SIZE * 21);
	if (!cub->data.img.img)
		return (perror("Fail to open img"), 1);
	cub->data.img.addr = mlx_get_data_addr(cub->data.img.img, &cub->data.img.bits_per_pixel,
										   &cub->data.img.line_length, &cub->data.img.endian);
	cub->data.img.mlx = cub->data.mlx;
	cub->data.img.win = cub->data.win;
	return (0);
}

void display_map(t_cub *cub)
{
	t_img img;
	char **map;
	int map_x;
	int map_y;

	map = cub->data.map.map;
	img = cub->data.img;
	map_y = 0;
	while (map[map_y])
	{
		map_x = 0;
		while (map[map_y][map_x])
		{
			if (map[map_y][map_x] == '1')
				fill_tile(&img, 0xFFFFFF, map_y, map_x);
			else
				fill_tile(&img, 0, map_y, map_x);
			map_x++;
		}
		map_y++;
	}
}

void set_player(t_cub *cub)
{
	char **map;
	int x;
	int y;

	y = 0;
	map = cub->data.map.map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (palyer_chars(map[y][x]))
			{
				cub->player.x = x;
				cub->player.y = y;
				cub->player.dir = map[y][x];
			}
			x++;
		}
		y++;
	}
	cub->player.x_bit = TILE_SIZE / 2;
	cub->player.y_bit = TILE_SIZE / 2;
}

void set_dirction(t_cub *cub)
{
	if (cub->player.dir == 'N')
		cub->player.angl = 90;
	if (cub->player.dir == 'S')
		cub->player.angl = -90;
	if (cub->player.dir == 'W')
		cub->player.angl = 180;
	if (cub->player.dir == 'E')
		cub->player.angl = 0;
}

void render_map(t_cub *cub)
{
	if (init_image(cub))
		return;
	display_map(cub);
	set_player(cub);
	set_dirction(cub);
	draw_player(&cub->data.img, cub->player, 0xFFFFFF);
	mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
}
