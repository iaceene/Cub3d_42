/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:35:35 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/31 15:41:20 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	touch_one(float px, float py, t_cub *cub)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if (cub->data.map.map[y][x] == '1' || cub->data.map.map[y][x] == '2')
		return (true);
	return (false);
}

float	use_distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	use_fixed_dist(float x1, float y1, float x2, float y2, t_cub *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = use_distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}
