/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:49:34 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/19 11:41:24 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void cast_ray(t_cub *cub, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = cub->player.x;
    float ray_y = cub->player.y;
    int j = 0;

    while (!touch_one(ray_x, ray_y, cub))
    {
        ray_x += cos_angle;
        ray_y += sin_angle;
        j++;
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

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}
void draw_split_background(t_cub *cub)
{
    int y = 0;
    int screen_middle = HEIGHT / 2;

    while (y < HEIGHT)
    {
        int x = 0;
        while (x < WIDTH)
        {
            if (y < screen_middle)
                my_pixel_put(x, y, &cub->data.img,
                             create_trgb(0, cub->texture->sky_grb[0],
                                         cub->texture->sky_grb[1],
                                         cub->texture->sky_grb[2]));
            else
                my_pixel_put(x, y, &cub->data.img,
                             create_trgb(0, cub->texture->floor_grb[0],
                                         cub->texture->floor_grb[1],
                                         cub->texture->floor_grb[2]));
            x++;
        }
        y++;
    }
}
// In raycaster.c (or wherever you draw the HUD)
void my_pixel_put_img(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}


void draw_weapon(t_cub *cub, int scale)
{
    int frame = cub->weapon_anim_active ? cub->weapon_anim_frame : 0;
    t_img *weapon = &cub->texture->weapon[cub->current_weapon_index * MAX_ANIM_FRAMES + frame];

    int x_start = (WIDTH - weapon->width * scale) / 2;
    int y_start = HEIGHT - weapon->height * scale;

    for (int y = 0; y < weapon->height; y++)
    {
        for (int x = 0; x < weapon->width; x++)
        {
            char *src_pixel = weapon->addr + (y * weapon->line_length + x * (weapon->bits_per_pixel / 8));
            unsigned int color = *(unsigned int*)src_pixel;

            if ((color & 0x00FFFFFF) != 0)
            {
                for (int dy = 0; dy < scale; dy++)
                    for (int dx = 0; dx < scale; dx++)
                        my_pixel_put_img(&cub->data.img,
                                         x_start + x * scale + dx,
                                         y_start + y * scale + dy,
                                         color);
            }
        }
    }

    // Animate on each game loop tick
    if (cub->weapon_anim_active)
    {
        cub->weapon_anim_tick++;
        if (cub->weapon_anim_tick > 5) // delay between frames
        {
            cub->weapon_anim_tick = 0;
            cub->weapon_anim_frame++;
            if (cub->weapon_anim_frame >= MAX_ANIM_FRAMES)
            {
                cub->weapon_anim_frame = 0;
                cub->weapon_anim_active = 0; // End animation
            }
        }
    }
}




int game_loop(t_cub *cub)
{
    handle_movement(cub);
    clear_image(cub);
    draw_split_background(cub);
    int scale = 3;

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
    draw_weapon(cub, scale);
    mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
    return (0);
}