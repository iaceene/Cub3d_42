/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:06:51 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/26 10:25:36 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void init_player(t_player *player, t_cub *cub)
{
    player->key_up = false;
    player->key_down = false;
    player->key_left = false;
    player->key_right = false;
    player->left_rotate = false;
    player->right_rotate = false;

    for (int y = 0; cub->data.map.map[y]; y++)
    {
        for (int x = 0; cub->data.map.map[y][x]; x++)
        {
            char dir = cub->data.map.map[y][x];
            if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
            {
                player->x = x * BLOCK + BLOCK / 2;
                player->y = y * BLOCK + BLOCK / 2;

                if (dir == 'N')
                    player->angle = PI / 2;
                else if (dir == 'S')
                    player->angle = 3 * PI / 2;
                else if (dir == 'E')
                    player->angle = 0;
                else if (dir == 'W')
                    player->angle = PI;

                cub->data.map.map[y][x] = '0';
                return;
            }
        }
    }
}

int init_image(t_cub *cub)
{
    cub->data.img.img = mlx_new_image(cub->data.mlx, WIDTH, HEIGHT);
    if (!cub->data.img.img)
        return (perror("Fail to open img"), 1);
    cub->data.img.addr = mlx_get_data_addr(cub->data.img.img, &cub->data.img.bits_per_pixel,
                                           &cub->data.img.line_length, &cub->data.img.endian);
    cub->data.img.mlx = cub->data.mlx;
    cub->data.img.win = cub->data.win;
    return (0);
}

int event_hook_window(t_cub *cub)
{
    mlx_hook(cub->data.win, 17, 0, close_window, cub);
    mlx_hook(cub->data.win, 2, 1L << 0, key_press, cub);
    mlx_hook(cub->data.win, 3, 1L << 1, key_release, cub);
    mlx_hook(cub->data.win, 6, 1L << 6, mouse_move, cub);
    mlx_hook(cub->data.win, 4, 1L << 2, mouse_scroll, cub);
    mlx_loop_hook(cub->data.mlx, game_loop, cub);

    mlx_loop(cub->data.mlx);
    return (0);
}

#define MAX_FRAMES 18

int init_textures_weapon(t_cub *cub)
{
    const char *paths[MAX_FRAMES] = {
        "./textures/player1/01.xpm",
        "./textures/player1/02.xpm",
        "./textures/player1/03.xpm",
        "./textures/player1/04.xpm",
        "./textures/player1/05.xpm",
        "./textures/player1/06.xpm",
        "./textures/player1/07.xpm",
        "./textures/player1/08.xpm",
        "./textures/player1/09.xpm",
        "./textures/player1/010.xpm",
        "./textures/player1/011.xpm",
        "./textures/player1/012.xpm",
        "./textures/player1/013.xpm",
        "./textures/player1/014.xpm",
        "./textures/player1/015.xpm",
        "./textures/player1/016.xpm",
        "./textures/player1/017.xpm",
        "./textures/player1/018.xpm"};

    cub->texture->weapon = malloc(sizeof(t_img) * MAX_FRAMES);
    if (!cub->texture->weapon)
    {
        ft_putendl_fd("Error\nMemory allocation failed for weapon textures", 2);
        exit(1);
    }

    for (int f = 0; f < MAX_FRAMES; f++)
    {
        cub->texture->weapon[f].img = mlx_xpm_file_to_image(
            cub->data.mlx,
            (char *)paths[f],
            &cub->texture->weapon[f].width,
            &cub->texture->weapon[f].height);

        if (!cub->texture->weapon[f].img)
        {
            ft_putendl_fd("Error\nFailed to load weapon texture", 2);
            exit(1);
        }

        cub->texture->weapon[f].addr = mlx_get_data_addr(
            cub->texture->weapon[f].img,
            &cub->texture->weapon[f].bits_per_pixel,
            &cub->texture->weapon[f].line_length,
            &cub->texture->weapon[f].endian);
    }
    cub->weapon_anim_speed = 1;

    cub->current_weapon_index = 1;
    cub->weapon_anim_frame = 1;
    cub->weapon_anim_active = 1;
    cub->weapon_anim_tick = 1;

    return 0;
}

void init_texture_wall(t_cub *cub)
{
    cub->texture->no_img.img = mlx_xpm_file_to_image(cub->data.mlx,
                                                     cub->texture->no_path, &cub->texture->no_img.width, &cub->texture->no_img.height);
    if (!cub->texture->no_img.img)
    {
        perror("Failed to load north texture");
        exit(1);
    }
    cub->texture->no_img.addr = mlx_get_data_addr(cub->texture->no_img.img,
                                                  &cub->texture->no_img.bits_per_pixel, &cub->texture->no_img.line_length,
                                                  &cub->texture->no_img.endian);

    cub->texture->so_img.img = mlx_xpm_file_to_image(cub->data.mlx,
                                                     cub->texture->so_path, &cub->texture->so_img.width, &cub->texture->so_img.height);
    if (!cub->texture->so_img.img)
        perror("Failed to load south texture");
    cub->texture->so_img.addr = mlx_get_data_addr(cub->texture->so_img.img,
                                                  &cub->texture->so_img.bits_per_pixel, &cub->texture->so_img.line_length,
                                                  &cub->texture->so_img.endian);

    cub->texture->we_img.img = mlx_xpm_file_to_image(cub->data.mlx,
                                                     cub->texture->we_path, &cub->texture->we_img.width, &cub->texture->we_img.height);
    if (!cub->texture->we_img.img)
        perror("Failed to load west texture");
    cub->texture->we_img.addr = mlx_get_data_addr(cub->texture->we_img.img,
                                                  &cub->texture->we_img.bits_per_pixel, &cub->texture->we_img.line_length,
                                                  &cub->texture->we_img.endian);

    cub->texture->ea_img.img = mlx_xpm_file_to_image(cub->data.mlx,
                                                     cub->texture->ea_path, &cub->texture->ea_img.width, &cub->texture->ea_img.height);
    if (!cub->texture->ea_img.img)
        perror("Failed to load east texture");
    cub->texture->ea_img.addr = mlx_get_data_addr(cub->texture->ea_img.img,
                                                  &cub->texture->ea_img.bits_per_pixel, &cub->texture->ea_img.line_length,
                                                  &cub->texture->ea_img.endian);
}
void init_texture_door(t_cub *cub)
{
    cub->texture->door_img.img = mlx_xpm_file_to_image(cub->data.mlx,
                                                       "./textures/door/door.xpm", &cub->texture->door_img.width, &cub->texture->door_img.height);
    if (!cub->texture->door_img.img)
    {
        ft_putendl_fd("Error\nFailed to load door texture", 2);
        exit(1);
    }
    cub->texture->door_img.addr = mlx_get_data_addr(cub->texture->door_img.img,
                                                    &cub->texture->door_img.bits_per_pixel, &cub->texture->door_img.line_length,
                                                    &cub->texture->door_img.endian);
}

void init_texture_floor(t_cub *cub)
{
    cub->texture->floor_img.img = mlx_xpm_file_to_image(cub->data.mlx,
                                                        "./textures/floor/floor.xpm", &cub->texture->floor_img.width, &cub->texture->floor_img.height);
    if (!cub->texture->floor_img.img)
    {
        ft_putendl_fd("Error\nFailed to load floor texture", 2);
        exit(1);
    }
    cub->texture->floor_img.addr = mlx_get_data_addr(cub->texture->floor_img.img,
                                                     &cub->texture->floor_img.bits_per_pixel, &cub->texture->floor_img.line_length,
                                                     &cub->texture->floor_img.endian);
}

void init_texture_door_anim(t_cub *cub)
{
    char *door_paths[MAX_DOOR_FRAMES] = {
        "./textures/door/__door1.xpm",
        "./textures/door/__door2.xpm",
        "./textures/door/door_01.xpm",
        "./textures/door/__door2.xpm"};

    for (int i = 0; i < MAX_DOOR_FRAMES; i++)
    {
        cub->door_textures[i].img = mlx_xpm_file_to_image(cub->data.mlx,
                                                          door_paths[i], &cub->door_textures[i].width, &cub->door_textures[i].height);
        if (!cub->door_textures[i].img)
        {
            ft_putendl_fd("Error loading door animation texture", 2);
            while (--i >= 0)
                mlx_destroy_image(cub->data.mlx, cub->door_textures[i].img);
            exit(EXIT_FAILURE);
        }
        cub->door_textures[i].addr = mlx_get_data_addr(cub->door_textures[i].img,
                                                       &cub->door_textures[i].bits_per_pixel, &cub->door_textures[i].line_length,
                                                       &cub->door_textures[i].endian);
    }

    cub->door_anim_active = 0;
    cub->door_anim_frame = 0;
    cub->door_anim_tick = 0;
}
void put_large_text(t_cub *cub, int frame_number)
{
    char path[256];
    snprintf(path, sizeof(path), "./textures/start%d.xpm", frame_number);

    int img_width, img_height;
    void *img = mlx_xpm_file_to_image(cub->data.mlx, path, &img_width, &img_height);
    if (!img)
    {
        printf("Failed to load large text image: %s\n", path);
        return;
    }

    int bpp, line_length, endian;
    unsigned int *src_pixels = (unsigned int *)mlx_get_data_addr(img, &bpp, &line_length, &endian);

    int win_x = WIDTH / 2 - img_width / 2;
    int win_y = HEIGHT - img_height - 30; // 30 pixels margin from bottom

    unsigned int *dst_pixels = (unsigned int *)cub->data.img.addr;
    int dst_line_len = cub->data.img.line_length;

    for (int y = 0; y < img_height; y++)
    {
        for (int x = 0; x < img_width; x++)
        {
            unsigned int color = src_pixels[y * (line_length / 4) + x];
            if ((color & 0x00FFFFFF) != 0x000000) // Skip black
            {
                int dst_x = win_x + x;
                int dst_y = win_y + y;
                if (dst_x >= 0 && dst_x < WIDTH && dst_y >= 0 && dst_y < HEIGHT)
                    dst_pixels[dst_y * (dst_line_len / 4) + dst_x] = color;
            }
        }
    }

    mlx_destroy_image(cub->data.mlx, img);

    // Show the updated image buffer
    mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
}

void init_texture_background_anim(t_cub *cub)
{
    char background_paths[256];

    for (int i = 0; i < MAX_BACKGROUND_FRAMES; i++)
    {
        float progress = (float)(i + 1) / MAX_BACKGROUND_FRAMES;
        int text_frame = 1;
        if (progress >= 0.75f)
            text_frame = 4;
        else if (progress >= 0.5f)
            text_frame = 3;
        else if (progress >= 0.25f)
            text_frame = 2;

        // Draw loading text (start1.xpm ... start4.xpm)
        put_large_text(cub, text_frame);

        snprintf(background_paths, sizeof(background_paths), "./textures/background/%d.xpm", i + 1);
        cub->background_textures[i].img = mlx_xpm_file_to_image(cub->data.mlx,
                                                                background_paths,
                                                                &cub->background_textures[i].width,
                                                                &cub->background_textures[i].height);

        if (!cub->background_textures[i].img)
        {
            ft_putendl_fd("Error loading background animation texture", 2);
            while (--i >= 0)
                mlx_destroy_image(cub->data.mlx, cub->background_textures[i].img);
            exit(EXIT_FAILURE);
        }

        // Put the background image centered or at (0,0)
        // If you want to center:
        int bg_x = WIDTH / 2 - cub->background_textures[i].width / 2;
        int bg_y = HEIGHT / 2 - cub->background_textures[i].height / 2;
        // Or simply at top-left (0,0):
        // int bg_x = 0, bg_y = 0;

        mlx_put_image_to_window(cub->data.mlx, cub->data.win,
                                cub->background_textures[i].img, bg_x, bg_y);

        char frame_text[52];
        snprintf(frame_text, sizeof(frame_text), "Loading %.0f %%", progress * 100.0f);
        mlx_string_put(cub->data.mlx, cub->data.win,
                       WIDTH / 2 - 50, HEIGHT - 30, 0X00FF00, frame_text);

        cub->background_textures[i].addr = mlx_get_data_addr(cub->background_textures[i].img,
                                                             &cub->background_textures[i].bits_per_pixel,
                                                             &cub->background_textures[i].line_length,
                                                             &cub->background_textures[i].endian);
    }
}


void see_texture_background(t_cub *cub)
{
    // Clear the screen

    // mlx_clear_window(cub->data.mlx, cub->data.win);
    // Display each texture in sequence with a small delay
    for (int i = 0; i < MAX_BACKGROUND_FRAMES; i++)
    {

        if (cub->background_textures[i].img)
        {
            // Clear previous frame
            mlx_clear_window(cub->data.mlx, cub->data.win);

            // Display current frame
            mlx_put_image_to_window(cub->data.mlx, cub->data.win,
                                    cub->background_textures[i].img, 0, 0);

            // Add frame number text
            char frame_text[52];
            snprintf(frame_text, sizeof(frame_text), "Loading %0.f %%", i * 1.9230);
            mlx_string_put(cub->data.mlx, cub->data.win,
                           WIDTH / 2 - 50, HEIGHT - 30, 0xFFFFFF, frame_text);

            // Force display update and add small delay
            mlx_do_sync(cub->data.mlx);
            usleep(100000); // 100ms delay between frames
        }
    }

    // After showing all frames, display a completion message
    mlx_clear_window(cub->data.mlx, cub->data.win);
    mlx_string_put(cub->data.mlx, cub->data.win,
                   WIDTH / 2 - 100, HEIGHT / 2, 0xFFFFFF, "The fun begins NOW!!");
    mlx_do_sync(cub->data.mlx);
    sleep(1); // Show message for 1 second
}

int init_window(t_cub *cub)
{
    cub->data.mlx = mlx_init();
    if (!cub->data.mlx)
        return (ft_putendl_fd("Error\nFail to create connection", 2), 1);
    cub->data.win = mlx_new_window(cub->data.mlx, WIDTH, HEIGHT, "Cub3d");
    if (!cub->data.win)
        return (ft_putendl_fd("Error\nFail to open window", 2), 1);
    cub->background_anim_frame = 0;
    cub->background_anim_tick = 0;

    init_player(&cub->player, cub);
    if (init_image(cub))
        return 1;
    init_textures_weapon(cub);
    init_texture_wall(cub);
    init_texture_door(cub);
    init_texture_floor(cub);
    init_texture_door_anim(cub);
    init_texture_background_anim(cub);
    // mlx_string_put(cub->data.mlx, cub->data.win,  WIDTH/ 2, HEIGHT / 2, 0X00FF00, "LOEDING");
    // sleep(3);
    // see_texture_background(cub);
    if (event_hook_window(cub))
        return (1);
    return (0);
}
