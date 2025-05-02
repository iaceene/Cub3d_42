/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 18:14:22 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/02 18:31:36 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void fill_tile(t_cub *cub, int clr, int y, int x)
{
	int hight;
	int width;
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
			mlx_pixel_put(mlx, win, (x * 64) + width, (y * 64) + hight, clr);
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
	
	map = cub->data.map.map;
	map_y = 0;
	while (map[map_y])
	{
		map_x = 0;
		while(map[map_y][map_x])
		{
			if (map[map_y][map_x] == '1')
				fill_tile(cub, 0x00FFFFFF, map_y, map_x);
			else if (map[map_y][map_x] == '0')
				fill_tile(cub, 0x00FFFF00, map_y, map_x);
			map_x++;
		}
		map_y++;
	}
}