/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:06:51 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/02 13:49:37 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	set_player_angle(t_player *player, char dir)
{
	if (dir == 'N')
		player->angle = PI / 2;
	else if (dir == 'S')
		player->angle = 3 * PI / 2;
	else if (dir == 'E')
		player->angle = 0;
	else if (dir == 'W')
		player->angle = PI;
}

void	init_player(t_player *player, t_cub *cub)
{
	int		x;
	int		y;
	char	dir;

	(1) && (player->key_up = false, player->key_down = false, \
		player->key_left = false, player->key_right = false, \
		player->left_rotate = false, player->right_rotate = false, y = 0);
	while (cub->data.map.map[y])
	{
		x = 0;
		while (cub->data.map.map[y][x])
		{
			dir = cub->data.map.map[y][x];
			if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
			{
				player->x = x * BLOCK + BLOCK / 2;
				player->y = y * BLOCK + BLOCK / 2;
				set_player_angle(player, dir);
				cub->data.map.map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

int	init_image(t_cub *cub)
{
	cub->data.img.img = mlx_new_image(cub->data.mlx, WIDTH, HEIGHT);
	if (!cub->data.img.img)
		return (perror("Fail to open img"), 1);
	cub->data.img.addr = mlx_get_data_addr(cub->data.img.img,
			&cub->data.img.bits_per_pixel,
			&cub->data.img.line_length,
			&cub->data.img.endian);
	cub->data.img.mlx = cub->data.mlx;
	cub->data.img.win = cub->data.win;
	return (0);
}

void	init_texture_door(t_cub *cub)
{
	cub->texture->door_img.img = mlx_xpm_file_to_image(cub->data.mlx,
			"./textures/door/__door2.xpm",
			&cub->texture->door_img.width,
			&cub->texture->door_img.height);
	if (!cub->texture->door_img.img)
	{
		ft_putendl_fd("Error\nFailed to load door texture", 2);
		exit(1);
	}
	cub->texture->door_img.addr = mlx_get_data_addr(cub->texture->door_img.img,
			&cub->texture->door_img.bits_per_pixel,
			&cub->texture->door_img.line_length,
			&cub->texture->door_img.endian);
}

int	init_window(t_cub *cub)
{
	cub->data.mlx = mlx_init();
	if (!cub->data.mlx)
		return (ft_putendl_fd("Error\nFail to create connection", 2), 1);
	cub->data.win = mlx_new_window(cub->data.mlx, WIDTH, HEIGHT, "Cub3d");
	if (!cub->data.win)
		return (ft_putendl_fd("Error\nFail to open window", 2), 1);
	init_player(&cub->player, cub);
	if (init_image(cub))
		return (1);
	init_textures_weapon(cub);
	init_texture_wall(cub);
	init_texture_door(cub);
	if (event_hook_window(cub))
		return (1);
	return (0);
}
