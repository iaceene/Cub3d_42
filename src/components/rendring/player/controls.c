/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:37:28 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/07 09:12:39 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"


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
