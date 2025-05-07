/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:46:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/07 09:14:35 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void render_draw_square(int x, int y, int size, int color, t_cub *cub)
{
	int i = 0;
	while (i < size)
	{
		my_pixel_put(x + i, y, &cub->data.img, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_pixel_put(x, y + i, &cub->data.img, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_pixel_put(x + size, y + i, &cub->data.img, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_pixel_put(x + i, y + size, &cub->data.img, color);
		i++;
	}
}


void render_draw_minimap(t_cub *cub)
{
	char **map;
	map = cub->data.map.map;
	for (int y = 0; map[y] && y < MAP_HEIGHT; y++)
	{
		for (int x = 0; map[y][x] && x < MAP_WIDTH; x++)
		{
			if (cub->data.map.map[y][x] == '1')
			{
				render_draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE,
							BLOCK_SIZE, 0x27d632, cub);
			}
		}
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

	for (int i = 0; i < steps; i++)
	{
		my_pixel_put((int)x, (int)y, &cub->data.img, 0x00FF00);
		x += x_inc;
		y += y_inc;
	}
}