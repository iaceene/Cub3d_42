/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:49:34 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/07 09:15:07 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void cast_ray(t_cub *cub, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = cub->player.x;
	float ray_y = cub->player.y;

	while (!touch_one(ray_x, ray_y, cub))
	{
		// my_pixel_put(ray_x, ray_y, &cub->data.img, 0xFF0000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	float dist = use_fixed_dist(cub->player.x, cub->player.y, ray_x, ray_y, cub);
	float height = (BLOCK / dist) * (WIDTH / 2);
	int start_y = (HEIGHT - height) / 2;
	int end = start_y + height;

	while (start_y < end && start_y < WIDTH)
	{
		my_pixel_put(i, start_y, &cub->data.img, 255);
		start_y++;
	}
}

int game_loop(t_cub *cub)
{
	handle_movement(cub);
	clear_image(cub);

	float fraction = PI / 3 / WIDTH;
	float start_x = cub->player.angle - PI / 6;
	int i = 0;
	while (i < WIDTH)
	{
		cast_ray(cub, start_x, i);
		start_x += fraction;
		i++;
	}

	render_draw_minimap(cub);
	mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
	return (0);
}
