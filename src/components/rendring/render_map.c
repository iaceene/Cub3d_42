/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:14:22 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/05 16:16:30 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)(img->addr + offset) = color;
}

void fill_tile(t_img *img, int clr, int y, int x)
{
	int 	hight;
	int 	width;

	hight = 0;
	while (hight < 64)
	{
		width = 0;
		while (width < 64)
		{
			my_pixel_put(x * 64 + width, y * 64 + hight, img, clr);
			width++;
		}
		hight++;
	}
}

void	draw_player(t_img *img, t_player point, int color)
{
	int i;

	i = 0;
	
	my_pixel_put(point.x * TILE_SIZE + point.x_bit, point.y * TILE_SIZE + point.y_bit , img, color);
	while (i < 4)
	{
		my_pixel_put(point.x * TILE_SIZE + point.x_bit + i, point.y * TILE_SIZE + point.y_bit , img, color);
		my_pixel_put(point.x * TILE_SIZE + point.x_bit, point.y * TILE_SIZE + point.y_bit + i, img, color);
		my_pixel_put(point.x * TILE_SIZE + point.x_bit - i, point.y * TILE_SIZE + point.y_bit , img, color);
		my_pixel_put(point.x * TILE_SIZE + point.x_bit, point.y * TILE_SIZE + point.y_bit - i, img, color);
		i++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

int	init_image(t_cub *cub)
{
	cub->data.img.img = mlx_new_image(cub->data.mlx, 64 * 21, 64 * 21);
	if (!cub->data.img.img)
		return (perror("Fail to open img"), 1);
	cub->data.img.addr = mlx_get_data_addr(cub->data.img.img, &cub->data.img.bits_per_pixel,
		&cub->data.img.line_length, &cub->data.img.endian);
	cub->data.img.mlx = cub->data.mlx;
	cub->data.img.win = cub->data.win;
	return (0);
}

void	display_map(t_cub *cub)
{
	t_img	img;
	char	**map;
	int		map_x;
	int		map_y;

	
	map = cub->data.map.map;
	img = cub->data.img;
	map_y = 0;
	while (map[map_y])
	{
		map_x = 0;
		while(map[map_y][map_x])
		{
			if (map[map_y][map_x] == '1')
				fill_tile(&img, 0xFFFFFF, map_y, map_x);
			else if (map[map_y][map_x] == '0')
				fill_tile(&img, 0, map_y, map_x);
			else
			{
				cub->player.x = map_x;
				cub->player.y = map_y;
				cub->player.x_bit = 32;
				cub->player.y_bit = 32;
				draw_player(&img, cub->player, 0xFFFFFF);
			}
			map_x++;
		}
		map_y++;
	}
}

void	render_map(t_cub *cub)
{
	if (init_image(cub))
		return ;
	display_map(cub);
	mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
}
