/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:49:34 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/07 13:24:48 by iezzam           ###   ########.fr       */
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
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    float dist = use_fixed_dist(cub->player.x, cub->player.y, ray_x, ray_y, cub);
    float height = (BLOCK / dist) * (WIDTH / 2);
    int start_y = (HEIGHT - height) / 2;
    int end = start_y + height;
    
    while (start_y < end && start_y < HEIGHT)
    {
        my_pixel_put(i, start_y, &cub->data.img, SKY_BOTTOM);
        start_y++;
    }
}

void draw_background(t_cub *cub)
{
    int y = 0;
    int screen_middle = HEIGHT / 2;
    
    while (y < HEIGHT)
    {
        int x = 0;
        while (x < WIDTH)
        {
            if (y < screen_middle)
                my_pixel_put(x, y, &cub->data.img, FLOOR_TOP);
            else
                my_pixel_put(x, y, &cub->data.img, FLOOR_BOTTOM);
            x++;
        }
        y++;
    }
}

int game_loop(t_cub *cub)
{
    handle_movement(cub);
    clear_image(cub);
    draw_background(cub);

    float fraction = PI / 3 / WIDTH;
    float start_x = cub->player.angle - PI / 6;
    for (int i = 0; i < WIDTH; i++)
    {
        cast_ray(cub, start_x, i);
        start_x += fraction;
    }

    render_draw_minimap(cub);
    mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
    return (0);
}