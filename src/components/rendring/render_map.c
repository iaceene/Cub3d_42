/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:14:22 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/02 19:36:14 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	my_pixel_put(int x, int y, t_cub *cub, int color)
{
	int	offset;

	offset = (y * cub->data.img.line_length) + (x * (cub->data.img.bits_per_pixel / 8));
	*(unsigned int *)(cub->data.img.addr + offset) = color;
}

void fill_tile(t_cub *cub, int clr, int y, int x)
{
	int 	hight;
	int 	width;
	void	*mlx;
	void	*win;

	hight = 0;
	mlx = cub->data.mlx;
	win = cub->data.win;
	while (hight < 64)
	{
		width = 0;
		while (width < 64)
		{
			my_pixel_put(x * 64 + width, y * 64 + hight, cub, clr);
			width++;
		}
		hight++;
	}
}

void	render_map(t_cub *cub)
{
	char	**map;
	int		map_x;
	int		map_y;
	
	void *img;
	char *data;
	int bpp, size_line, endian;


	img = mlx_new_image(cub->data.mlx, 64 * 21, 64 * 21);
	
	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

	map = cub->data.map.map;
	map_y = 0;

	cub->data.img.addr = data;
	cub->data.img.bits_per_pixel = bpp;
	cub->data.img.endian = endian;
	cub->data.img.line_length = size_line;
	while (map[map_y])
	{
		map_x = 0;
		while(map[map_y][map_x])
		{
			if (map[map_y][map_x] == '1')
				fill_tile(cub, 0, map_y, map_x);
			else if (map[map_y][map_x] == '0')
				fill_tile(cub, 0xFFFF00, map_y, map_x);
			map_x++;
		}
		map_y++;
	}
	mlx_put_image_to_window(cub->data.mlx, cub->data.win, img, 0, 0);
}
