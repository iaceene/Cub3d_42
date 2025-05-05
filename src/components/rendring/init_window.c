/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:30:30 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/05 18:33:33 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	log_state(t_cub *cub)
{
	printf("[X = %d]\n[Y = %d]\n", (cub->player.x_bit + cub->player.x) * 64,
		(cub->player.y_bit + cub->player.y) * 64);
}

int	is_wall_point(t_cub *cub, int x, int y)
{
	size_t	i;

	i = 0;
	while (i < cub->data.map.map_points)
	{
		if (x == cub->wall[i].x && y == cub->wall[i].y)
			return (printf("wall hitted\n"), 1);
		i++;
	}
	printf("no wall\n");
	return (0);
}

int	close_window(void	*pram)
{
	t_cub *cub;

	printf(COLOR_RED    "[CLOSING WINDOW]" COLOR_RESET "\n");
	cub = (t_cub *)pram;
	mlx_destroy_window(cub->data.mlx, cub->data.win);
	ft_malloc(-1);
	printf(COLOR_GREEN    "[WINDOW CLOSED]" COLOR_RESET "\n");
	exit(0);
}

void	move_down(t_cub *cub)
{
	log_state(cub);
	if (is_wall_point(cub, cub->player.x_bit, cub->player.y_bit))
		return ;
	draw_player(&cub->data.img, cub->player, 0);
	cub->player.y_bit += MOVE_SPEED;
	draw_player(&cub->data.img, cub->player, 0xFFFFFF);
	mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
}

void	move_up(t_cub *cub)
{
	log_state(cub);
	if (is_wall_point(cub, cub->player.x_bit, cub->player.y_bit))
		return ;
	draw_player(&cub->data.img, cub->player, 0);
	cub->player.y_bit -= MOVE_SPEED;
	draw_player(&cub->data.img, cub->player, 0xFFFFFF);
	mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
}

void	move_left(t_cub *cub)
{
	log_state(cub);
	if (is_wall_point(cub, cub->player.x_bit, cub->player.y_bit))
		return ;
	draw_player(&cub->data.img, cub->player, 0);
	cub->player.x_bit -= MOVE_SPEED;
	draw_player(&cub->data.img, cub->player, 0xFFFFFF);
	mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
}

void	move_right(t_cub *cub)
{
	log_state(cub);
	if (is_wall_point(cub, cub->player.x_bit, cub->player.y_bit))
		return ;
	draw_player(&cub->data.img, cub->player, 0);
	cub->player.x_bit += MOVE_SPEED;
	draw_player(&cub->data.img, cub->player, 0xFFFFFF);
	mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
}

int	key_bind(int key, void *pram)
{
	t_cub *cub;

	cub = (t_cub *)pram;
	if (key == XK_Escape)
		close_window(cub);
	if (key == XK_w)
		move_up(cub);
	if (key == XK_s)
		move_down(cub);
	if (key == XK_d)
		move_right(cub);
	if (key == XK_a)
		move_left(cub);
	return (0);
}

int	cub_window(t_cub *cub)
{
	mlx_hook(cub->data.win, 17, 0, close_window, cub);
	mlx_hook(cub->data.win, 2, 1L<<0, key_bind, cub);
	render_map(cub);
	mlx_loop(cub->data.mlx);
	return (0);
}

int	init_window(t_cub *cub)
{
	int		hight;
	int		width;

	cub->data.mlx = mlx_init();
	if (!cub->data.mlx)
		return (ft_putendl_fd("Error\nFail to create connection", 2), 1);
	mlx_get_screen_size(cub->data.mlx, &hight, &width);
	cub->screen_h = hight;
	cub->screen_w = width;
	cub->data.map.map_points = cub->data.map.width * 64 * cub->data.map.height * 64;
	// cub->data.win = mlx_new_window(cub->data.mlx, hight, width, "Cub3d");
	cub->data.win = mlx_new_window(cub->data.mlx, cub->data.map.width * 64, cub->data.map.height * 64, "Cub3d");
	if (!cub->data.win)
		return (ft_putendl_fd("Error\nFail to open window", 2), 1);
	printf(COLOR_GREEN   "[WINDOW CREATED]  " COLOR_RESET "\n");
	if (cub_window(cub))
		return (1);
	return (0);
}
