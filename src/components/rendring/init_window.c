/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:30:30 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/10 03:32:34 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void log_state(t_cub *cub)
{
	printf("[%f %f]\n", cub->player.x * TILE_SIZE + cub->player.x_bit,
		   cub->player.y * TILE_SIZE + cub->player.y_bit);
}

int is_wall_point(t_cub *cub, int x, int y)
{
	size_t i;

	i = 0;
	log_state(cub);
	while (i < cub->data.map.map_points)
	{
		if (x == cub->wall[i].x && y == cub->wall[i].y)
			return (printf("Wall\n"), 1);
		i++;
	}
	return (0);
}

int close_window(void *pram)
{
	t_cub *cub;

	printf(COLOR_RED "[CLOSING WINDOW]" COLOR_RESET "\n");
	cub = (t_cub *)pram;
	mlx_destroy_window(cub->data.mlx, cub->data.win);
	ft_malloc(-1);
	printf(COLOR_GREEN "[WINDOW CLOSED]" COLOR_RESET "\n");
	exit(0);
}

void move_player(t_cub *cub, float speed, int flag)
{
	draw_player(&cub->data.img, cub->player, 0);
	display_map(cub);

	if (flag)
		cub->player.x_bit += speed;
	cub->player.y_bit += speed;

	draw_player(&cub->data.img, cub->player, 0xFFFFFF);
}

void move_cam(t_cub *cub, int i)
{
	display_map(cub);
	if (!i)
		cub->player.angl -= CAM_SPEED;
	else
		cub->player.angl += CAM_SPEED;
	draw_player(&cub->data.img, cub->player, 0xFFFFFF);
}

int key_bind(int key, void *pram)
{
	t_cub *cub;

	cub = (t_cub *)pram;
	if (key == XK_Escape)
		close_window(cub);
	if (key == XK_w)
		cub->player.y_bit -= MOVE_SPEED;
	if (key == XK_s)
		cub->player.y_bit += MOVE_SPEED;
	if (key == XK_d)
		cub->player.x_bit += MOVE_SPEED;
	if (key == XK_a)
		cub->player.x_bit -= MOVE_SPEED;
	if (key == XK_Left)
		move_cam(cub, 1);
	if (key == XK_Right)
		move_cam(cub, 0);
	display_map(cub);
	draw_player(&cub->data.img, cub->player, 0xFFFFFF);
	return (0);
}

int cub_window(t_cub *cub)
{
	render_map(cub);
	mlx_hook(cub->data.win, 17, 0, close_window, cub);
	mlx_hook(cub->data.win, 2, 1L << 0, key_bind, cub);
	mlx_loop(cub->data.mlx);
	return (0);
}

int init_window(t_cub *cub)
{
	int hight;
	int width;

	cub->data.mlx = mlx_init();
	if (!cub->data.mlx)
		return (ft_putendl_fd("Error\nFail to create connection", 2), 1);
	mlx_get_screen_size(cub->data.mlx, &hight, &width);
	cub->screen_h = hight;
	cub->screen_w = width;
	cub->player.cub = cub;
	cub->data.win = mlx_new_window(cub->data.mlx, hight, width, "Cub3d");
	if (!cub->data.win)
		return (ft_putendl_fd("Error\nFail to open window", 2), 1);
	printf(COLOR_GREEN "[WINDOW CREATED]  \n" COLOR_RESET);
	if (cub_window(cub))
		return (1);
	return (0);
}
