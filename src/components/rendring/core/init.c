/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:06:51 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/15 10:47:29 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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
	mlx_loop_hook(cub->data.mlx, game_loop, cub);

	mlx_loop(cub->data.mlx);
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
	// init_textures(cub); 
	if (event_hook_window(cub))
		return (1);
	return (0);
}	