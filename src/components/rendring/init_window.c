/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:30:30 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/05 15:38:42 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool touch_one(float px, float py, t_cub *cub);

int close_window(t_cub *cub)
{
	mlx_destroy_window(cub->data.mlx, cub->data.win);
	exit(0);
	return (0);
}

void init_player(t_player *player, t_cub *cub)
{
	player->angle = PI / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;

	player->left_rotate = false;
	player->right_rotate = false;

	int y = 0;
	int x = 0;
	while (cub->data.map.map[y])
	{
		x = 0;
		while (cub->data.map.map[y][x])
		{
			if (cub->data.map.map[y][x] == 'N')
			{
				player->x = x * BLOCK + BLOCK / 2;
				player->y = y * BLOCK + BLOCK / 2;
				cub->data.map.map[y][x] = '0';
				return;
			}
			x++;
		}
		y++;
	}
}

int key_press(int key, t_cub *cub)
{
	if (key == XK_Escape)
		close_window(cub);
	if (key == 119 || key == 65362)
		cub->player.key_up = true;
	if (key == 115 || key == 65364)
		cub->player.key_down = true;
	if (key == 97 || key == 65361)
		cub->player.key_left = true;
	if (key == 100 || key == 65363)
		cub->player.key_right = true;
	if (key == LEFT)
		cub->player.left_rotate = true;
	if (key == RIGHT)
		cub->player.right_rotate = true;
	return (0);
}

int key_release(int key, t_cub *cub)
{
	if (key == XK_Escape)
		close_window(cub);
	if (key == 119 || key == 65362)
		cub->player.key_up = false;
	if (key == 115 || key == 65364)
		cub->player.key_down = false;
	if (key == 97 || key == 65361)
		cub->player.key_left = false;
	if (key == 100 || key == 65363)
		cub->player.key_right = false;
	if (key == LEFT)
		cub->player.left_rotate = false;
	if (key == RIGHT)
		cub->player.right_rotate = false;

	return (0);
}

void move_player(t_cub *cub)
{

	int speed = 3;
	float angle_speed = 0.03;
	float cos_angle = cos(cub->player.angle);
	float sin_angle = sin(cub->player.angle);
	float new_x = cub->player.x;
	float new_y = cub->player.y;

	if (cub->player.left_rotate)
		cub->player.angle -= angle_speed;
	if (cub->player.right_rotate)
		cub->player.angle += angle_speed;
	if (cub->player.angle > 2 * PI)
		cub->player.angle = 0;
	if (cub->player.angle < 0)
		cub->player.angle = 2 * PI;

	if (cub->player.key_up)
	{
		new_x += cos_angle * speed;
		new_y += sin_angle * speed;
	}
	if (cub->player.key_down)
	{
		new_x -= cos_angle * speed;
		new_y -= sin_angle * speed;
	}
	if (cub->player.key_left)
	{
		new_x += sin_angle * speed;
		new_y -= cos_angle * speed;
	}
	if (cub->player.key_right)
	{
		new_x -= sin_angle * speed;
		new_y += cos_angle * speed;
	}

	if (!touch_one(new_x, new_y, cub))
	{
		cub->player.x = new_x;
		cub->player.y = new_y;
	}
}

void clear_image(t_cub *cub)
{
	int x = 0;
	int y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_pixel_put(x, y, &cub->data.img, 0);
			x++;
		}
		y++;
	}
}

bool touch_one(float px, float py, t_cub *cub)
{
	int x = px / BLOCK;
	int y = py / BLOCK;

	if (cub->data.map.map[y][x] == '1')
		return true;
	return false;
}

void draw_square(int x, int y, int size, int color, t_cub *cub)
{
	int i = 0;
	while (i < size)
	{
		my_pixel_put(x + i, y, &cub->data.img, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_pixel_put(x, y + i, &cub->data.img, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_pixel_put(x + size, y + i, &cub->data.img, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_pixel_put(x + i, y + size, &cub->data.img, color);
		i++;
	}
}

void draw_map(t_cub *cub)
{
	char **map;
	int color;
	int y;
	int x;

	map = cub->data.map.map;
	color = 0x0000FF;
	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, cub);
			x++;
		}
		y++;
	}
}

float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_cub *game)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return fix_dist;
}

void draw_line(t_cub *cub, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = cub->player.x;
	float ray_y = cub->player.y;

	while (!touch_one(ray_x, ray_y, cub))
	{
		my_pixel_put(ray_x, ray_y, &cub->data.img, 0xFF0000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	float dist = fixed_dist(cub->player.x, cub->player.y, ray_x, ray_y, cub);
	float height = (BLOCK / dist) * (WIDTH / 2);
	int start_y = (HEIGHT - height) / 2;
	int end = start_y + height;

	while (start_y < end && start_y < WIDTH)
	{
		my_pixel_put(i, start_y, &cub->data.img, 255);
		start_y++;
	}
}
int draw_loop(t_cub *cub)
{
	move_player(cub);
	clear_image(cub);
	draw_map(cub);
	float fraction = PI / 3 / WIDTH;
	float start_x = cub->player.angle - PI / 6;
	int i = 0;
	while (i < WIDTH)
	{
		draw_line(cub, start_x, i);
		start_x += fraction;
		i++;
	}

	mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
	return (0);
}

int cub_window(t_cub *cub)
{
	mlx_hook(cub->data.win, 17, 0, close_window, cub);
	mlx_hook(cub->data.win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->data.win, 3, 1L << 1, key_release, cub);
	mlx_loop_hook(cub->data.mlx, draw_loop, cub);

	mlx_loop(cub->data.mlx);
	return (0);
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
int init_window(t_cub *cub)
{
	cub->data.mlx = mlx_init();
	if (!cub->data.mlx)
		return (ft_putendl_fd("Error\nFail to create connection", 2), 1);
	cub->data.win = mlx_new_window(cub->data.mlx, WIDTH, HEIGHT, "Cub3d");
	if (!cub->data.win)
		return (ft_putendl_fd("Error\nFail to open window", 2), 1);
	init_player(&cub->player, cub);
	if (init_image(cub))
		return 1;
	if (cub_window(cub))
		return (1);
	return (0);
}
