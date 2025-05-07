/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:55:45 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/07 09:12:43 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int close_window(t_cub *cub)
{
	mlx_destroy_window(cub->data.mlx, cub->data.win);
	exit(0);
	return (0);
}

void handle_movement(t_cub *cub)
{

	int speed = 100;
	float rotation_speed = 0.10;
	float cos_angle = cos(cub->player.angle);
	float sin_angle = sin(cub->player.angle);
	float new_x = cub->player.x;
	float new_y = cub->player.y;

	if (cub->player.left_rotate)
		cub->player.angle -= rotation_speed;
	if (cub->player.right_rotate)
		cub->player.angle += rotation_speed;
	if (cub->player.angle > 2 * PI)
		cub->player.angle = 0;
	if (cub->player.angle < 0)
		cub->player.angle = 2 * PI;

	if (cub->player.key_up)
	{
		new_x += cos_angle * speed;
		new_y += sin_angle * speed;
	}
	if (cub->player.key_down)
	{
		new_x -= cos_angle * speed;
		new_y -= sin_angle * speed;
	}
	if (cub->player.key_left)
	{
		new_x += sin_angle * speed;
		new_y -= cos_angle * speed;
	}
	if (cub->player.key_right)
	{
		new_x -= sin_angle * speed;
		new_y += cos_angle * speed;
	}

	if (!touch_one(new_x, new_y, cub))
	{
		cub->player.x = new_x;
		cub->player.y = new_y;
	}
}
