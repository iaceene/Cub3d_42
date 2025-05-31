/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:49:21 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/31 14:49:47 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"



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
    int win_y = HEIGHT - img_height - 30;

    unsigned int *dst_pixels = (unsigned int *)cub->data.img.addr;
    int dst_line_len = cub->data.img.line_length;

    for (int y = 0; y < img_height; y++)
    {
        for (int x = 0; x < img_width; x++)
        {
            unsigned int color = src_pixels[y * (line_length / 4) + x];
            if ((color & 0x00FFFFFF) != 0x000000)
            {
                int dst_x = win_x + x;
                int dst_y = win_y + y;
                if (dst_x >= 0 && dst_x < WIDTH && dst_y >= 0 && dst_y < HEIGHT)
                    dst_pixels[dst_y * (dst_line_len / 4) + dst_x] = color;
            }
        }
    }

    mlx_destroy_image(cub->data.mlx, img);

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

        int bg_x = WIDTH / 2 - cub->background_textures[i].width / 2;
        int bg_y = HEIGHT / 2 - cub->background_textures[i].height / 2;
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