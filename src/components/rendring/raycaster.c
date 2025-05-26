/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:49:34 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/25 22:26:07 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool is_block(float px, float py, t_cub *cub, char type)
{
    int x = (int)(px) / BLOCK;
    int y = (int)(py) / BLOCK;

    if (cub->data.map.map[y][x] == type)
        return (true);
    return (false);
}

void draw_wall(t_cub *cub, int screen_x, float ray_dx, float ray_dy,
               float ray_x, float ray_y, int side, float dist)
{
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
        if (ray_dx < 0)
            tex = &cub->texture->we_img;
        else
            tex = &cub->texture->ea_img;
        wall_hit = fmod(ray_y, BLOCK) / BLOCK;
    }
    else
    {
        if (ray_dy < 0)
            tex = &cub->texture->no_img;
        else
            tex = &cub->texture->so_img;
        wall_hit = fmod(ray_x, BLOCK) / BLOCK;
    }

    int tex_x = (int)(wall_hit * tex->width);
    if ((side == 0 && ray_dx > 0) || (side == 1 && ray_dy < 0))
        tex_x = tex->width - tex_x - 1;

    float step = (float)tex->height / wall_height;
    float tex_pos = (start_y - HEIGHT / 2 + wall_height / 2) * step;

    int y = start_y;
    while (y < end_y)
    {
        int tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += step;
        char *pixel = tex->addr + (tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8));
        int color = *(unsigned int *)pixel;
        my_pixel_put(screen_x, y, &cub->data.img, color);
        y++;
    }
}
void draw_door(t_cub *cub, int screen_x, float ray_dx, float ray_dy,
               float ray_x, float ray_y, int side, float dist)
{
    float wall_height = (BLOCK / dist) * (WIDTH / 2);
    int start_y = (HEIGHT - wall_height) / 2;
    if (start_y < 0)
        start_y = 0;
    int end_y = start_y + wall_height;
    if (end_y > HEIGHT)
        end_y = HEIGHT;

    t_img *tex = NULL;
    if (cub->door_anim_active)
        tex = &cub->door_textures[cub->door_anim_frame];
    else
        tex = &cub->door_textures[0];

    if (!tex || !tex->img)
        return;

    float wall_hit;
    if (side == 0)
        wall_hit = fmod(ray_y, BLOCK) / BLOCK;
    else
        wall_hit = fmod(ray_x, BLOCK) / BLOCK;

    int tex_x = (int)(wall_hit * tex->width);
    if ((side == 0 && ray_dx > 0) || (side == 1 && ray_dy < 0))
        tex_x = tex->width - tex_x - 1;

    float step = (float)tex->height / wall_height;
    float tex_pos = (start_y - HEIGHT / 2 + wall_height / 2) * step;

    int y = start_y;
    while (y < end_y)
    {
        int tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += step;
        char *pixel = tex->addr + (tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8));
        int color = *(unsigned int *)pixel;
        my_pixel_put(screen_x, y, &cub->data.img, color);
        y++;
    }
}

void cast_ray(t_cub *cub, float ray_angle, int screen_x)
{
    float ray_dir_x = cos(ray_angle);
    float ray_dir_y = sin(ray_angle);

    int map_x = (int)cub->player.x / BLOCK;
    int map_y = (int)cub->player.y / BLOCK;

    float side_dist_x;
    float side_dist_y;

    float delta_dist_x = fabs(1 / ray_dir_x);
    float delta_dist_y = fabs(1 / ray_dir_y);

    int step_x;
    int step_y;
    int side;

    float pos_x = cub->player.x;
    float pos_y = cub->player.y;

    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (pos_x - map_x * BLOCK) * delta_dist_x / BLOCK;
    }
    else
    {
        step_x = 1;
        side_dist_x = ((map_x + 1) * BLOCK - pos_x) * delta_dist_x / BLOCK;
    }

    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (pos_y - map_y * BLOCK) * delta_dist_y / BLOCK;
    }
    else
    {
        step_y = 1;
        side_dist_y = ((map_y + 1) * BLOCK - pos_y) * delta_dist_y / BLOCK;
    }

    char hit_tile = ' ';
    while (1)
    {
        if (side_dist_x < side_dist_y)
        {
            map_x += step_x;
            side_dist_x += delta_dist_x;
            side = 0;
        }
        else
        {
            map_y += step_y;
            side_dist_y += delta_dist_y;
            side = 1;
        }

        hit_tile = cub->data.map.map[map_y][map_x];
        if (hit_tile == '1' || hit_tile == '2')
            break;
    }

    float hit_x, hit_y;
    if (side == 0)
    {
        hit_x = cub->player.x + (map_x * BLOCK - cub->player.x + (1 - step_x) * BLOCK / 2) / ray_dir_x * ray_dir_x;
        hit_y = cub->player.y + (map_x * BLOCK - cub->player.x + (1 - step_x) * BLOCK / 2) / ray_dir_x * ray_dir_y;
    }
    else
    {
        hit_x = cub->player.x + (map_y * BLOCK - cub->player.y + (1 - step_y) * BLOCK / 2) / ray_dir_y * ray_dir_x;
        hit_y = cub->player.y + (map_y * BLOCK - cub->player.y + (1 - step_y) * BLOCK / 2) / ray_dir_y * ray_dir_y;
    }

    float dist = use_fixed_dist(cub->player.x, cub->player.y, hit_x, hit_y, cub);

    if (hit_tile == '2')
        draw_door(cub, screen_x, ray_dir_x, ray_dir_y, hit_x, hit_y, side, dist);
    else
        draw_wall(cub, screen_x, ray_dir_x, ray_dir_y, hit_x, hit_y, side, dist);
}

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

void draw_split_background(t_cub *cub)
{
    int screen_middle = HEIGHT / 2;

    int floor_width = cub->texture->floor_img.width;
    int floor_height = cub->texture->floor_img.height;

    float posX = cub->player.x;
    float posY = cub->player.y;

    float planeX = cos(cub->player.angle + PI / 2) * 0.66f;
    float planeY = sin(cub->player.angle + PI / 2) * 0.66f;
    int y = screen_middle;

    while (y < HEIGHT)
    {
        float rayDirZ = (float)(y - HEIGHT / 2);
        float rowDistance = (float)(HEIGHT / 2) / rayDirZ;

        int x = 0;
        while (x < WIDTH)
        {
            float cameraX = 2 * x / (float)WIDTH - 1;
            float rayDirX = cos(cub->player.angle) + planeX * cameraX;
            float rayDirY = sin(cub->player.angle) + planeY * cameraX;
            float floorX = posX + rowDistance * rayDirX;
            float floorY = posY + rowDistance * rayDirY;
            int tx = (int)(floorX * floor_width) % floor_width;
            int ty = (int)(floorY * floor_height) % floor_height;

            if (tx < 0)
                tx += floor_width;
            if (ty < 0)
                ty += floor_height;

            char *pixel_addr = cub->texture->floor_img.addr + (ty * cub->texture->floor_img.line_length) + (tx * (cub->texture->floor_img.bits_per_pixel / 8));
            unsigned int color = *(unsigned int *)pixel_addr;

            my_pixel_put(x, y, &cub->data.img, color);
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
void draw_weapon(t_cub *cub)
{

    cub->weapon_anim_tick++;
    if (cub->weapon_anim_tick > cub->weapon_anim_speed)
    {
        cub->weapon_anim_tick = 0;
        cub->weapon_anim_frame++;
        if (cub->weapon_anim_frame >= MAX_ANIM_FRAMES)
            cub->weapon_anim_frame = 0;
    }

    int frame = cub->weapon_anim_frame;
    t_img *weapon = &cub->texture->weapon[cub->current_weapon_index * MAX_ANIM_FRAMES + frame];

    int scaled_width = weapon->width / 2;
    int scaled_height = weapon->height / 2;

    int x_start = (WIDTH - scaled_width) / 2;
    int y_start = HEIGHT - scaled_height / 1.2;

    for (int y = 0; y < scaled_height; y++)
    {
        for (int x = 0; x < scaled_width; x++)
        {
            int orig_x = x * 2;
            int orig_y = y * 2;

            char *src_pixel = weapon->addr + (orig_y * weapon->line_length + orig_x * (weapon->bits_per_pixel / 8));
            unsigned int color = *(unsigned int *)src_pixel;

            if ((color & 0x00FFFFFF) != 0)
            {
                my_pixel_put_img(&cub->data.img, x_start + x, y_start + y, color);
            }
        }
    }
}

void update_door_animation(t_cub *cub)
{
    if (!cub->door_anim_active)
        return;

    cub->door_anim_tick++;
    if (cub->door_anim_tick > 8)
    {
        cub->door_anim_tick = 0;
        cub->door_anim_frame++;

        if (cub->door_anim_frame >= 4)
        {
            cub->door_anim_frame = 0;
            cub->door_anim_active = 0;

            cub->data.map.map[cub->door_y][cub->door_x] = 'D';
        }
    }
}

void update_door_close(t_cub *cub)
{
    if (!cub->door_opened)
        return;

    if (cub->door_anim_active)
        return;

    int px = (int)(cub->player.x / BLOCK);
    int py = (int)(cub->player.y / BLOCK);

    int fx = px + (int)round(cos(cub->player.angle));
    int fy = py + (int)round(sin(cub->player.angle));
    int player_is_facing_door = (fx == cub->door_x && fy == cub->door_y);
    int player_is_on_door = (px == cub->door_x && py == cub->door_y);

    if (!player_is_facing_door && !player_is_on_door)
    {
        cub->door_anim_tick = 0;
        cub->door_anim_frame = 0;
        cub->door_anim_active = 0;
        cub->door_opened = 0;
        cub->data.map.map[cub->door_y][cub->door_x] = '2';
    }
}

// Gets color from a texture at specific coordinates
int get_pixel_color(t_img *img, int x, int y)
{
    char *dst;

    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return 0;
    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    return *(unsigned int *)dst;
}

// Puts a pixel to the screen image
void put_pixel_to_img(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}
#define BACKGROUND_ANIM_SPEED 1
void draw_background(t_cub *cub)
{
    t_img *current_frame;
    int x;
    int y;

    // Get the current animation frame
    current_frame = &cub->background_textures[cub->background_anim_frame];

    // Draw the background animation frame to cover the entire screen
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            // Calculate the position in the texture (modulo for repeating pattern if needed)
            int tex_x = x % current_frame->width;
            int tex_y = y % current_frame->height;

            // Get the color from the texture
            int color = get_pixel_color(current_frame, tex_x, tex_y);

            // Put the pixel to the screen
            if (color != 0x000000)
                put_pixel_to_img(&cub->data, x, y, color);

            x++;
        }
        y++;
    }

    // Update animation frame counter
    cub->background_anim_tick++;
    if (cub->background_anim_tick >= BACKGROUND_ANIM_SPEED)
    {
        cub->background_anim_tick = 0;
        cub->background_anim_frame = (cub->background_anim_frame + 1) % MAX_BACKGROUND_FRAMES;
    }
}

int game_loop(t_cub *cub)
{

    handle_movement(cub);
    clear_image(cub);

    draw_split_background(cub);

    float ray_step = (PI / 3) / WIDTH;
    float ray_angle = cub->player.angle - (PI / 6);

    int x = 0;
    while (x < WIDTH)
    {
        cast_ray(cub, ray_angle, x);
        ray_angle += ray_step;
        x++;
    }
    // static int i = 0;
    // if (i <= 30)
    //     draw_background(cub);
    // i++;
    render_draw_minimap(cub);
    draw_weapon(cub);
    update_door_animation(cub);
    // update_door_close(cub);
    mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
    return 0;
}
