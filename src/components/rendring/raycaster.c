/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:49:34 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/20 17:15:29 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void cast_ray(t_cub *cub, float ray_angle, int screen_x)
{
    float ray_x = cub->player.x;
    float ray_y = cub->player.y;
    float ray_dx = cos(ray_angle);
    float ray_dy = sin(ray_angle);

    int side;
    float wall_x;

    while (!touch_one(ray_x, ray_y, cub))
    {
        if (touch_one(ray_x + ray_dx, ray_y, cub))
        {
            side = 0;
            wall_x = ray_y;
            break;
        }
        if (touch_one(ray_x, ray_y + ray_dy, cub))
        {
            side = 1;
            wall_x = ray_x;
            break;
        }
        ray_x += ray_dx;
        ray_y += ray_dy;
    }

    float dist = use_fixed_dist(cub->player.x, cub->player.y, ray_x, ray_y, cub);
    float wall_height = (BLOCK / dist) * (WIDTH / 2);
    int start_y = (HEIGHT - wall_height) / 2;
    if (start_y < 0)
        start_y = 0;
    int end_y = start_y + wall_height;
    if (end_y > HEIGHT)
        end_y = HEIGHT;

    t_img *tex;
    float wall_hit;

    if (side == 0)
    {
        tex = ray_dx < 0 ? &cub->texture->we_img : &cub->texture->ea_img;
        wall_hit = fmod(ray_y, BLOCK) / BLOCK;
    }
    else
    {
        tex = ray_dy < 0 ? &cub->texture->no_img : &cub->texture->so_img;
        wall_hit = fmod(ray_x, BLOCK) / BLOCK;
    }

    int tex_x = (int)(wall_hit * tex->width);
    if ((side == 0 && ray_dx > 0) || (side == 1 && ray_dy < 0))
        tex_x = tex->width - tex_x - 1;

    float step = (float)tex->height / wall_height;
    float tex_pos = (start_y - HEIGHT / 2 + wall_height / 2) * step;

    for (int y = start_y; y < end_y; y++)
    {
        int tex_y = (int)tex_pos & (tex->height - 1); // safer than modulo
        tex_pos += step;
        char *pixel = tex->addr + (tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8));
        int color = *(unsigned int *)pixel;
        my_pixel_put(screen_x, y, &cub->data.img, color);
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
void my_pixel_put_img(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
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
            unsigned int color = *(unsigned int *)src_pixel;

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

    if (cub->weapon_anim_active)
    {
        cub->weapon_anim_tick++;
        if (cub->weapon_anim_tick > 5)
        {
            cub->weapon_anim_tick = 0;
            cub->weapon_anim_frame++;
            if (cub->weapon_anim_frame >= MAX_ANIM_FRAMES)
            {
                cub->weapon_anim_frame = 0;
                cub->weapon_anim_active = 0;
            }
        }
    }
}

int game_loop(t_cub *cub)
{
    handle_movement(cub);
    clear_image(cub);
    draw_split_background(cub);

    float ray_step = (PI / 3) / WIDTH;
    float ray_angle = cub->player.angle - (PI / 6);

    for (int x = 0; x < WIDTH; x++)
    {
        cast_ray(cub, ray_angle, x);
        ray_angle += ray_step;
    }

    render_draw_minimap(cub);
    draw_weapon(cub, 3);
    mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
    return 0;
}
