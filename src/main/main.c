/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:10:00 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/04 20:06:32 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include "../../mlx/mlx.h"

#define MOVE_SPEED 1
#define TILE_SIZE 64
#define WINDOW_WIDTH (TILE_SIZE * 20)
#define WINDOW_HEIGHT (TILE_SIZE * 20)


typedef struct s_img
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_img;

typedef struct s_point
{
    int     x;
    int     y;
    int     pos_pix_x;
    int     pos_pix_y;
} t_point;

typedef struct s_list
{
    void *win;
    void *mlx;
    t_img *img;
    t_point p;
} t_list;

void my_pixel_put(int x, int y, t_img *img, int color)
{
    int offset;

    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
        *(unsigned int *)(img->addr + offset) = color;
    }
}

void fill_tile(t_img *img, int clr, int y, int x)
{
    int hight;
    int width;

    hight = 0;
    while (hight < TILE_SIZE)
    {
        width = 0;
        while (width < TILE_SIZE)
        {
            my_pixel_put(x * TILE_SIZE + width, y * TILE_SIZE + hight, img, clr);
            width++;
        }
        hight++;
    }
}

void init_image(t_list *data)
{
    if (data->img)
        mlx_destroy_image(data->mlx, data->img->img);
    
    data->img = malloc(sizeof(t_img));
    data->img->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel,
        &data->img->line_length, &data->img->endian);
}

void    draw_player(t_list *data)
{
    int x = data->p.x;
    int y = data->p.y;


    my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x, y * TILE_SIZE + data->p.pos_pix_y, data->img, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

void fill_background(t_list *data)
{
    int y = 0;
    int x = 0;

    init_image(data);
    while (y < WINDOW_HEIGHT / TILE_SIZE)
    {
        x = 0;
        while (x < WINDOW_WIDTH / TILE_SIZE)
        {
            if (data->p.x != x || data->p.y != y)
                fill_tile(data->img, 0xFFFFFF, y, x);
            else
                fill_tile(data->img, 0x00FFFF, y, x);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

int close_window(void *param)
{
    t_list *cub = (t_list *)param;

    printf("[CLOSING WINDOW]\n");
    if (cub->img)
    {
        mlx_destroy_image(cub->mlx, cub->img->img);
        free(cub->img);
    }
    mlx_destroy_window(cub->mlx, cub->win);
    printf("[WINDOW CLOSED]\n");
    exit(0);
}

int key_bind(int key, void *param)
{
    t_list *data = (t_list *)param;

    if (key == XK_Escape)
        close_window(data);
	// if (key == XK_w)
	// 	move_up(data);
	// if (key == XK_s)
	// 	move_down(data);
	// if (key == XK_d)
	// 	move_right(data);
	// if (key == XK_a)
	// 	move_left(data);
    return (0);
}

int main()
{
    t_list data;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "test");
    data.img = NULL;
    data.p.x = 0;
    data.p.y = 0;
    data.p.pos_pix_x = 32;
    data.p.pos_pix_y = 32;
    fill_background(&data);
    draw_player(&data);
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_hook(data.win, 2, 1L<<0, key_bind, &data);
    mlx_loop(data.mlx);
    return (0);
}