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
#include <strings.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include "../../mlx/mlx.h"

#define MOVE_SPEED 4
#define TILE_SIZE 64
#define WINDOW_WIDTH (TILE_SIZE * 10)
#define WINDOW_HEIGHT (TILE_SIZE * 10)


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

typedef struct s_wall
{
    int     x;
    int     y;
} t_wall;

typedef struct s_list
{
    void *win;
    void *mlx;
    t_img *img;
    t_point p;
    t_wall *wall;
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

    int i = 0;


    my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x, y * TILE_SIZE + data->p.pos_pix_y, data->img, 0x00FF00);
    
    while (i < 4)
    {
        my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x + i, y * TILE_SIZE + data->p.pos_pix_y, data->img, 0x00FF00);
        my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x - i, y * TILE_SIZE + data->p.pos_pix_y, data->img, 0x00FF00);
        my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x, y * TILE_SIZE + data->p.pos_pix_y + i, data->img, 0x00FF00);
        my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x, y * TILE_SIZE + data->p.pos_pix_y - i, data->img, 0x00FF00);
        i++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}


int is_wall(int x, int y, t_list *data)
{
    int i = 0;
    while (i < (WINDOW_HEIGHT * WINDOW_WIDTH))
    {
        if (data->wall[i].x == x && data->wall[i].y == y)
            return(1);
        i++;
    }
    return (0);
}

void draw_walls(t_list *data)
{
    int y;
    int x;

    y = 0;
    x = 0;
    int i = 0;
    while (y < WINDOW_HEIGHT)
    {
        x = 0;
        while (x < WINDOW_WIDTH)
        {
            if ((y >= 0 && y <= 3)
            || (x >= 0 && x <= 3)
            || (y + 3 == WINDOW_HEIGHT)
            || (y + 2 == WINDOW_HEIGHT)
            || (y + 1 == WINDOW_HEIGHT)
            || (x + 3 == WINDOW_WIDTH)
            || (x + 2 == WINDOW_WIDTH)
            || (x + 1 == WINDOW_WIDTH))
            {
                my_pixel_put(x, y, data->img, 0x00FF00);
                data->wall[i].x = x;
                data->wall[i].y = y;
                i++;
            }
            x++;
        }
        y++;
    }
}

void    clear_player(t_list *data)
{
    int x = data->p.x;
    int y = data->p.y;

    int i = 0;


    // my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x, y * TILE_SIZE + data->p.pos_pix_y, data->img, 0xFFFFFF);
    
    while (i < 3)
    {
        my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x + i, y * TILE_SIZE + data->p.pos_pix_y, data->img, 0xFFFFFF);
        my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x - i, y * TILE_SIZE + data->p.pos_pix_y, data->img, 0xFFFFFF);
        my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x, y * TILE_SIZE + data->p.pos_pix_y + i, data->img, 0xFFFFFF);
        my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x, y * TILE_SIZE + data->p.pos_pix_y - i, data->img, 0xFFFFFF);
        i++;
    }
    i = 0;
    while (i < 2)
    {
        my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x + i, y * TILE_SIZE + data->p.pos_pix_y, data->img, 0);
        my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x - i, y * TILE_SIZE + data->p.pos_pix_y, data->img, 0);
        my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x, y * TILE_SIZE + data->p.pos_pix_y + i, data->img, 0);
        my_pixel_put(x * TILE_SIZE + data->p.pos_pix_x, y * TILE_SIZE + data->p.pos_pix_y - i, data->img, 0);
        i++;
    }
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
            fill_tile(data->img, 0xFFFFFF, y, x);
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

void print_log(int Px, int Py)
{
    printf("[log] Player X = %d Y = %d\n", Px, Py);
}

void move_down(t_list *data)
{
    if (is_wall(data->p.pos_pix_x, data->p.pos_pix_y + 1, data))
        return ;
    clear_player(data);
    draw_walls(data);
    data->p.pos_pix_y += MOVE_SPEED;
    print_log(data->p.pos_pix_x, data->p.pos_pix_y);
    draw_player(data);
}

void move_up(t_list *data)
{
    if (is_wall(data->p.pos_pix_x, data->p.pos_pix_y - 1, data))
        return ;
    clear_player(data);
    draw_walls(data);
    data->p.pos_pix_y -= MOVE_SPEED;
    print_log(data->p.pos_pix_x, data->p.pos_pix_y);
    draw_player(data);
}

void move_right(t_list *data)
{
    if (is_wall(data->p.pos_pix_x + 1, data->p.pos_pix_y, data))
        return ;
    clear_player(data);
    draw_walls(data);
    data->p.pos_pix_x += MOVE_SPEED;
    print_log(data->p.pos_pix_x, data->p.pos_pix_y);
    draw_player(data);
}

void move_left(t_list *data)
{
    if (is_wall(data->p.pos_pix_x - 1, data->p.pos_pix_y, data))
        return ;
    clear_player(data);
    draw_walls(data);
    data->p.pos_pix_x -= MOVE_SPEED;
    print_log(data->p.pos_pix_x, data->p.pos_pix_y);
    draw_player(data);
}

int key_bind(int key, void *param)
{
    t_list *data = (t_list *)param;

    if (key == XK_Escape)
        close_window(data);
	if (key == XK_w)
		move_up(data);
	if (key == XK_s)
		move_down(data);
	if (key == XK_d)
		move_right(data);
	if (key == XK_a)
		move_left(data);
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
    data.wall = malloc(sizeof(t_wall) * WINDOW_HEIGHT * WINDOW_WIDTH);
    if (!data.wall)
        return (1);
    bzero(data.wall, sizeof(t_wall) * WINDOW_HEIGHT * WINDOW_WIDTH);
    fill_background(&data);
    draw_walls(&data);
    draw_player(&data);
    mlx_hook(data.win, 17, 0, close_window, &data);
    mlx_hook(data.win, 2, 1L<<0, key_bind, &data);
    mlx_loop(data.mlx);
    return (0);
}