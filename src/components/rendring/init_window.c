/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:30:30 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/03 21:47:52 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int close_window(t_cub *cub)
{
	mlx_destroy_window(cub->data.mlx, cub->data.win);
	exit(0);
	return (0);
}

void init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
}

int key_press(int key, t_cub *cub)
{
	if (key == W)
		cub->player.key_up = true;
	else if (key == S)
		cub->player.key_down = true;
	else if (key == A)
		cub->player.key_left = true;
	else if (key == D)
		cub->player.key_right = true;
	else if (key == XK_Escape)
		close_window(cub);
	return (0);
}

int key_release(int key, t_cub *cub)
{
	if (key == W)
		cub->player.key_up = false;
	else if (key == S)
		cub->player.key_down = false;
	else if (key == A)
		cub->player.key_left = false;
	else if (key == D)
		cub->player.key_right = false;
	return (0);
}

void move_player(t_cub *cub)
{
	int speed = 5;

	if (cub->player.key_up)
		cub->player.y -= speed;
	if (cub->player.key_down)
		cub->player.x += speed;
	if (cub->player.key_left)
		cub->player.y -= speed;
	if (cub->player.key_right)
		cub->player.x += speed;
}

void clear_image(t_cub *cub)
{
	(void)cub;
	for(int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			my_pixel_put(x, y, 0, 0xFF);
		}
		
	}
}

int draw_loop(t_cub *cub)
{
	move_player(cub);
	clear_image(cub);
	render_map(cub);
	mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
	return (0);
}

int cub_window(t_cub *cub)
{
	mlx_hook(cub->data.win, 17, 0, close_window, cub);
	mlx_hook(cub->data.win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->data.win, 3, 1L << 1, key_release, cub);
	mlx_loop_hook(cub->data.mlx, draw_loop, cub);

	render_map(cub);

	mlx_loop(cub->data.mlx);
	return (0);
}

int init_window(t_cub *cub)
{
	cub->data.mlx = mlx_init();
	if (!cub->data.mlx)
		return (ft_putendl_fd("Error\nFail to create connection", 2), 1);
	cub->data.win = mlx_new_window(cub->data.mlx, 21 * 64, 21 * 64, "Cub3d");
	if (!cub->data.win)
		return (ft_putendl_fd("Error\nFail to open window", 2), 1);
	init_player(&cub->player);
	if (cub_window(cub))
		return (1);
	return (0);
}
