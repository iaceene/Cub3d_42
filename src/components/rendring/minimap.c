/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneki <kaneki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:46:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/01 20:37:20 by kaneki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void render_draw_square(int x, int y, int size, int color, t_cub *cub)
{
    int i;
    int j;

    i = 0;
    j = 0;
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

void draw_minimap_background(t_cub *cub, int center_x, int center_y, int radius)
{
    int y = center_y - radius;
    while (y <= center_y + radius)
    {
        int x = center_x - radius;
        while (x <= center_x + radius)
        {
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
            {
                const int dx = x - center_x;
                const int dy = y - center_y;
                if (dx * dx + dy * dy <= radius * radius)
                    my_pixel_put(x, y, &cub->data.img, 0x101010 - 0x87CEEB);
            }
            x++;
        }
        y++;
    }
}
// Add this helper function at the top or in a utils file
static int get_map_height(char **map)
{
    int h = 0;
    while (map && map[h])
        h++;
    return h;
}
void draw_minimap_doors(t_cub *cub, int center_x, int center_y, int radius)
{
    const int player_map_x = cub->player.x / BLOCK;
    const int player_map_y = cub->player.y / BLOCK;
    const int visible_blocks = radius / BLOCK_SIZE;
    int map_height = get_map_height(cub->data.map.map);


    int dy = -visible_blocks;
    while (dy <= visible_blocks)
    {
        int dx = -visible_blocks;
        while (dx <= visible_blocks)
        {
            const int map_x = player_map_x + dx;
            const int map_y = player_map_y + dy;
            if (map_y >= 0 && map_y < map_height && cub->data.map.map[map_y])
            {
                size_t row_len = ft_strlen(cub->data.map.map[map_y]);
                if (map_x >= 0 && map_x < (int)row_len && cub->data.map.map[map_y][map_x] == '2')
                {
                    const int screen_x = center_x + dx * BLOCK_SIZE;
                    const int screen_y = center_y + dy * BLOCK_SIZE;
                    const int dist_sq = (screen_x - center_x) * (screen_x - center_x) +
                                        (screen_y - center_y) * (screen_y - center_y);
                    if (dist_sq <= radius * radius)
                    {
                        render_draw_square(screen_x - BLOCK_SIZE / 2,
                                           screen_y - BLOCK_SIZE / 2,
                                           BLOCK_SIZE, DOOR_COLOR, cub);
                    }
                }
            }
            dx++;
        }
        dy++;
    }
}

void draw_minimap_walls(t_cub *cub, int center_x, int center_y, int radius)
{
    const int player_map_x = cub->player.x / BLOCK;
    const int player_map_y = cub->player.y / BLOCK;
    const int visible_blocks = radius / BLOCK_SIZE;
    int map_height = get_map_height(cub->data.map.map);

    int dy = -visible_blocks;
    while (dy <= visible_blocks)
    {
        int dx = -visible_blocks;
        while (dx <= visible_blocks)
        {
            const int map_x = player_map_x + dx;
            const int map_y = player_map_y + dy;
            if (map_y >= 0 && map_y < map_height && cub->data.map.map[map_y])
            {
                size_t row_len = ft_strlen(cub->data.map.map[map_y]);
                if (map_x >= 0 && map_x < (int)row_len && cub->data.map.map[map_y][map_x] == '1')
                {
                    const int screen_x = center_x + dx * BLOCK_SIZE;
                    const int screen_y = center_y + dy * BLOCK_SIZE;
                    const int dist_sq = (screen_x - center_x) * (screen_x - center_x) +
                                        (screen_y - center_y) * (screen_y - center_y);
                    if (dist_sq <= radius * radius)
                    {
                        render_draw_square(screen_x - BLOCK_SIZE / 2,
                                           screen_y - BLOCK_SIZE / 2,
                                           BLOCK_SIZE, WALL_COLOR, cub);
                    }
                }
            }
            dx++;
        }
        dy++;
    }
}

void draw_minimap_border(t_cub *cub, int center_x, int center_y, int radius, int border_width)
{
    const int outer_radius = radius + border_width;
    int y = center_y - outer_radius;

    while (y <= center_y + outer_radius)
    {
        int x = center_x - outer_radius;
        while (x <= center_x + outer_radius)
        {
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
            {
                const int dx = x - center_x;
                const int dy = y - center_y;
                const int dist_sq = dx * dx + dy * dy;
                if (dist_sq <= outer_radius * outer_radius && dist_sq > radius * radius)
                    my_pixel_put(x, y, &cub->data.img, 0x000000);
            }
            x++;
        }
        y++;
    }
}

void draw_minimap_direction(t_cub *cub, int center_x, int center_y, int radius)
{
    const float line_length = 40.0f;
    float dx = cosf(cub->player.angle);
    float dy = sinf(cub->player.angle);
    float x = center_x;
    float y = center_y;

    for (int i = 0; i < (int)line_length; i++)
    {
        int px = (int)x;
        int py = (int)y;
        if ((px - center_x) * (px - center_x) + (py - center_y) * (py - center_y) > radius * radius)
            break;
        if (touch_one(px, py, cub))
            my_pixel_put(px, py, &cub->data.img, 0xFF0000);
        else
            break;
        x += dx;
        y += dy;
    }
}

void draw_minimap_player(t_cub *cub, int center_x, int center_y)
{
    int player_size = PLAYER_SIZE;
    int py = -player_size;
    while (py <= player_size)
    {
        int px = -player_size;
        while (px <= player_size)
        {
            if (px * px + py * py <= player_size * player_size)
                my_pixel_put(center_x + px, center_y + py, &cub->data.img, PLAYER_COLOR);
            px++;
        }
        py++;
    }
}

void render_draw_minimap(t_cub *cub)
{
    const int offset_x = WIDTH - MINIMAP_WIDTH - 10;
    const int offset_y = HEIGHT - MINIMAP_HEIGHT - 10;
    const int center_x = offset_x + MINIMAP_WIDTH / 2;
    const int center_y = offset_y + MINIMAP_HEIGHT / 2;
    const int radius = MINIMAP_WIDTH / 2 - 5;
    const int border_width = 6;

    draw_minimap_background(cub, center_x, center_y, radius);
    draw_minimap_walls(cub, center_x, center_y, radius);
    draw_minimap_doors(cub, center_x, center_y, radius);
    draw_minimap_border(cub, center_x, center_y, radius, border_width);
    draw_minimap_player(cub, center_x, center_y);
    draw_minimap_direction(cub, center_x, center_y, radius);
}