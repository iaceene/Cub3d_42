/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:06:51 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/19 14:17:33 by iezzam           ###   ########.fr       */
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
	mlx_hook(cub->data.win, 6, 1L << 6, mouse_move, cub);
	mlx_hook(cub->data.win, 4, 1L << 2, mouse_scroll, cub);
	mlx_loop_hook(cub->data.mlx, game_loop, cub);

	mlx_loop(cub->data.mlx);
	return (0);
}


// int init_textures(t_cub *cub)
// {
//     char *paths[MAX_WEAPONS] = {
//         "./textures/player/weapon.xpm",
//         "./textures/player/weapon_axe_sentienttest.xpm",
//         "./textures/player/weapon_cleaver_sentienttest.xpm"
//     };
// 	cub->texture->weapon = malloc(sizeof(t_img) * MAX_WEAPONS);
// 	if (!cub->texture->weapon)
// 	{
// 		ft_putendl_fd("Error\nMemory allocation failed for weapon textures", 2);
// 		exit(1);
// 	}

//     for (int i = 0; i < MAX_WEAPONS; i++)
//     {
//         cub->texture->weapon[i].img = mlx_xpm_file_to_image(
//             cub->data.mlx,
//             paths[i],
//             &cub->texture->weapon[i].width,
//             &cub->texture->weapon[i].height
//         );
//         if (!cub->texture->weapon[i].img)
//         {
//             ft_putendl_fd("Error\nFailed to load weapon texture", 2);
//             exit(1);
//         }
//         cub->texture->weapon[i].addr = mlx_get_data_addr(
//             cub->texture->weapon[i].img,
//             &cub->texture->weapon[i].bits_per_pixel,
//             &cub->texture->weapon[i].line_length,
//             &cub->texture->weapon[i].endian
//         );
//     }

//     cub->current_weapon_index = 0;
//     return 0;
// }

int init_textures(t_cub *cub)
{
    char *paths[MAX_WEAPONS][MAX_ANIM_FRAMES] = {
        {
            "./textures/player/weapon.xpm",
            "./textures/player/weapon_cleaver_sentienttest.xpm",
            "./textures/player/weapon.xpm"
        },
        {
            "./textures/player/weapon_axe_sentienttest.xpm",
            "./textures/player/weapon_axe_sentienttest.xpm",
            "./textures/player/weapon_axe_sentienttest.xpm"
        },
        {
            "./textures/player/weapon_cleaver_sentienttest.xpm",
            "./textures/player/weapon_cleaver_sentienttest.xpm",
            "./textures/player/weapon_cleaver_sentienttest.xpm"
        }
    };

    // Allocate array for all weapon frames
    cub->texture->weapon = malloc(sizeof(t_img) * MAX_WEAPONS * MAX_ANIM_FRAMES);
    if (!cub->texture->weapon)
    {
        ft_putendl_fd("Error\nMemory allocation failed for weapon textures", 2);
        exit(1);
    }

    for (int i = 0; i < MAX_WEAPONS; i++)
    {
        for (int f = 0; f < MAX_ANIM_FRAMES; f++)
        {
            int index = i * MAX_ANIM_FRAMES + f;

            cub->texture->weapon[index].img = mlx_xpm_file_to_image(
                cub->data.mlx,
                paths[i][f],
                &cub->texture->weapon[index].width,
                &cub->texture->weapon[index].height
            );

            if (!cub->texture->weapon[index].img)
            {
                ft_putendl_fd("Error\nFailed to load weapon texture", 2);
                exit(1);
            }

            cub->texture->weapon[index].addr = mlx_get_data_addr(
                cub->texture->weapon[index].img,
                &cub->texture->weapon[index].bits_per_pixel,
                &cub->texture->weapon[index].line_length,
                &cub->texture->weapon[index].endian
            );
        }
    }

    // Set initial state
    cub->current_weapon_index = 0;
    cub->weapon_anim_frame = 0;
    cub->weapon_anim_active = 0;
    cub->weapon_anim_tick = 0;

    return 0;
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
	init_textures(cub); 
	if (event_hook_window(cub))
		return (1);
	return (0);
}	