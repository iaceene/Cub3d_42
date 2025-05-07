/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:49:34 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/07 13:13:27 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Color Definitions */
#define SKY_TOP 0x1E90FF      // Dodger Blue
#define SKY_BOTTOM 0x87CEEB   // Light Sky Blue
#define FLOOR_TOP 0x696969    // Dim Gray
#define FLOOR_BOTTOM 0x36454F // Charcoal
#define WALL_TOP 0x6B8E23     // Olive Drab
#define WALL_BOTTOM 0x98FB98  // Pale Green

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
    
    // Wall gradient effect
    // int wall_height = end - start_y;
    while (start_y < end && start_y < HEIGHT)
    {
        float ratio = (float)(start_y - ((HEIGHT - height) / 2)) / height;
        int r = (int)((WALL_TOP >> 16 & 0xFF) * (1 - ratio) + (WALL_BOTTOM >> 16 & 0xFF) * ratio);
        int g = (int)((WALL_TOP >> 8 & 0xFF) * (1 - ratio) + (WALL_BOTTOM >> 8 & 0xFF) * ratio);
        int b = (int)((WALL_TOP & 0xFF) * (1 - ratio) + (WALL_BOTTOM & 0xFF) * ratio);
        int color = (r << 16) | (g << 8) | b;
        
        my_pixel_put(i, start_y, &cub->data.img, color);
        start_y++;
    }
}

void draw_background(t_cub *cub)
{
    int y = 0;
    int screen_middle = HEIGHT / 2;
    
    while (y < screen_middle)
    {
        float ratio = (float)y / screen_middle;
        int r = (int)((SKY_TOP >> 16 & 0xFF) * (1 - ratio) + (SKY_BOTTOM >> 16 & 0xFF) * ratio);
        int g = (int)((SKY_TOP >> 8 & 0xFF) * (1 - ratio) + (SKY_BOTTOM >> 8 & 0xFF) * ratio);
        int b = (int)((SKY_TOP & 0xFF) * (1 - ratio) + (SKY_BOTTOM & 0xFF) * ratio);
        int color = (r << 16) | (g << 8) | b;
        
        for (int x = 0; x < WIDTH; x++)
            my_pixel_put(x, y, &cub->data.img, color);
        y++;
    }
    
    while (y < HEIGHT)
    {
        float ratio = (float)(y - screen_middle) / screen_middle;
        int r = (int)((FLOOR_TOP >> 16 & 0xFF) * (1 - ratio) + (FLOOR_BOTTOM >> 16 & 0xFF) * ratio);
        int g = (int)((FLOOR_TOP >> 8 & 0xFF) * (1 - ratio) + (FLOOR_BOTTOM >> 8 & 0xFF) * ratio);
        int b = (int)((FLOOR_TOP & 0xFF) * (1 - ratio) + (FLOOR_BOTTOM & 0xFF) * ratio);
        int color = (r << 16) | (g << 8) | b;
        
        for (int x = 0; x < WIDTH; x++)
            my_pixel_put(x, y, &cub->data.img, color);
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