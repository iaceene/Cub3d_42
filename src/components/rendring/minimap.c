/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:46:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/15 09:41:17 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void render_draw_square(int x, int y, int size, int color, t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	j  = 0;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			if (i == 0 || j == 0 || i == size || j == size)
				my_pixel_put(x + i, y + j, &cub->data.img, color - 0x101010);
			else
				my_pixel_put(x + i, y + j, &cub->data.img, color);
			j++;
		}
		i++;
	}
}

void render_draw_minimap(t_cub *cub)
{
	char **map;
	int X;
	int Y;
	int i;

	map = cub->data.map.map;
	Y = 0;
	while (map[Y] && Y < MAP_HEIGHT)
	{
		X = 0;
		while (map[Y][X] && X < MAP_WIDTH)
		{
			if (cub->data.map.map[Y][X] == '1')
			{
				render_draw_square(X * BLOCK_SIZE, Y * BLOCK_SIZE,
								   BLOCK_SIZE, WALL_COLOR, cub);
			}
			else
			{
				render_draw_square(X * BLOCK_SIZE, Y * BLOCK_SIZE,
								   BLOCK_SIZE, EMPTY_SPACE, cub);
			}
			X++;
		}
		Y++;
	}

	float mini_player_x = world_to_minimap_x(cub->player.x);
	float mini_player_y = world_to_minimap_y(cub->player.y);

	render_draw_square(mini_player_x - PLAYER_SIZE / 2,
					   mini_player_y - PLAYER_SIZE / 2,
					   PLAYER_SIZE, 0xFF0000, cub);

	float line_length = PLAYER_SIZE * 2;
	float end_x = mini_player_x + cos(cub->player.angle) * line_length;
	float end_y = mini_player_y + sin(cub->player.angle) * line_length;

	float dx = end_x - mini_player_x;
	float dy = end_y - mini_player_y;
	float steps = fmax(fabs(dx), fabs(dy));
	float x_inc = dx / steps;
	float y_inc = dy / steps;
	float x = mini_player_x;
	float y = mini_player_y;

	i = 0;
	while (i < steps)
	{
		my_pixel_put((int)x, (int)y, &cub->data.img, RAY_COLOR);
		x += x_inc;
		y += y_inc;
		i++;
	}
}
