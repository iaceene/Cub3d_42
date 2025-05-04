/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:30:30 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/04 17:31:54 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	printf("x = %d\ny = %d\n", cub->player.x, cub->player.y);
	if (cub->player.y >= cub->data.map.height - 1)
		return ;
	if (cub->data.map.map[cub->player.y + 1][cub->player.x] == '1')
		return ;
	draw_player(&cub->data.img, cub->player.x, cub->player.y, 0);
	cub->player.y++;
	draw_player(&cub->data.img, cub->player.x, cub->player.y, 0xFF0000);
	mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
}

void	move_up(t_cub *cub)
{
	printf("x = %d\ny = %d\n", cub->player.x, cub->player.y);
	if (cub->player.y <= 0)
		return ;
	if (cub->data.map.map[cub->player.y - 1][cub->player.x] == '1')
		return ;
	draw_player(&cub->data.img, cub->player.x, cub->player.y, 0);
	cub->player.y--;
	draw_player(&cub->data.img, cub->player.x, cub->player.y, 0xFF0000);
	mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
}

void	move_left(t_cub *cub)
{
	printf("x = %d\ny = %d\n", cub->player.x, cub->player.y);
	if (cub->player.x <= 0)
		return ;
	if (cub->data.map.map[cub->player.y][cub->player.x - 1] == '1')
		return ;
	draw_player(&cub->data.img, cub->player.x, cub->player.y, 0);
	cub->player.x--;
	draw_player(&cub->data.img, cub->player.x, cub->player.y, 0xFF0000);
	mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
}

void	move_right(t_cub *cub)
{
	printf("x = %d\ny = %d\n", cub->player.x, cub->player.y);
	if (cub->player.x >= cub->data.map.width - 1)
		return ;
	if (cub->data.map.map[cub->player.y][cub->player.x + 1] == '1')
		return ;
	draw_player(&cub->data.img, cub->player.x, cub->player.y, 0);
	cub->player.x++;
	draw_player(&cub->data.img, cub->player.x, cub->player.y, 0xFF0000);
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
	// cub->data.win = mlx_new_window(cub->data.mlx, hight, width, "Cub3d");
	cub->data.win = mlx_new_window(cub->data.mlx, 21 * 64, 21 * 64, "Cub3d");
	if (!cub->data.win)
		return (ft_putendl_fd("Error\nFail to open window", 2), 1);
	printf(COLOR_GREEN   "[WINDOW CREATED]  " COLOR_RESET "\n");
	if (cub_window(cub))
		return (1);
	return (0);
}
