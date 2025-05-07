/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:44:54 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/07 08:45:58 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void my_pixel_put(int x, int y, t_img *img, int color)
{
	int offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)(img->addr + offset) = color;
}

void clear_image(t_cub *cub)
{
	int x = 0;
	int y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_pixel_put(x, y, &cub->data.img, 0);
			x++;
		}
		y++;
	}
}
