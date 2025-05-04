/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:14:22 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/04 17:11:58 by yaajagro         ###   ########.fr       */
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

void	draw_player(t_img *img, int xp, int yp, int color)
{
	// fill_tile(img, 0x00FFFF, yp, xp);

	int x = 0;
	int y = 0;

	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			my_pixel_put(xp * 64 + x, yp * 64 + y , img, color);
			x++;
		}
		y++;
	}
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
				draw_player(&img, map_x, map_y, 0xFF0000);
				cub->player.x = map_x;
				cub->player.y = map_y;
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
