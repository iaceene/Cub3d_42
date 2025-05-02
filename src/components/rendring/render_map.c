/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:14:22 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/02 23:16:02 by yaajagro         ###   ########.fr       */
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

void	draw_circle(t_img *img, int xp, int yp, int color)
{
	int		center_x;
	int		center_y;
	int		x;
	int		y;
	int		dis;

	fill_tile(img, 0, yp, xp);
	center_x = xp * 64 + 64 / 2;
	center_y = yp * 64 + 64 / 2;
	y = -20;
	while (y <= 10)
	{
		x = -20;
		while (x <= 10)
		{
			dis = x * x + y * y;
			if (dis <= 10 * 10)
				my_pixel_put(center_x + x, center_y + y, img, color);
			x++;
		}
		y++;
	}
}

int	init_image(t_img *img, t_cub *cub)
{
	img->img = mlx_new_image(cub->data.mlx, 64 * 21, 64 * 21);
	if (!img->img)
		return (perror("Fail to open img"), 1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);
	img->mlx = cub->data.mlx;
	img->win = cub->data.win;
	return (0);
}

void	render_map(t_cub *cub)
{
	t_img	img;
	char	**map;
	int		map_x;
	int		map_y;

	map_y = 0;
	map = cub->data.map.map;
	if (init_image(&img, cub))
		return ;
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
				draw_circle(&img, map_x, map_y, 0xFF0000);
			map_x++;
		}
		map_y++;
	}
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
}
