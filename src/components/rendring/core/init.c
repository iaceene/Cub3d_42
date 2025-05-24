/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:06:51 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/24 21:31:21 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void init_player(t_player *player, t_cub *cub)
{
    player->key_up = false;
    player->key_down = false;
    player->key_left = false;
    player->key_right = false;
    player->left_rotate = false;
    player->right_rotate = false;

    for (int y = 0; cub->data.map.map[y]; y++)
    {
        for (int x = 0; cub->data.map.map[y][x]; x++)
        {
            char dir = cub->data.map.map[y][x];
            if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
            {
                player->x = x * BLOCK + BLOCK / 2;
                player->y = y * BLOCK + BLOCK / 2;

                if (dir == 'N')
                    player->angle = PI / 2;
                else if (dir == 'S')
                    player->angle = 3 * PI / 2;
                else if (dir == 'E')
                    player->angle = 0;
                else if (dir == 'W')
                    player->angle = PI;

                cub->data.map.map[y][x] = '0';
                return;
            }
        }
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

    cub->current_weapon_index = 0;
    cub->weapon_anim_frame = 0;
    cub->weapon_anim_active = 0;
    cub->weapon_anim_tick = 0;

    return 0;
}

void init_texture_wall(t_cub *cub)
{
    cub->texture->no_img.img = mlx_xpm_file_to_image(cub->data.mlx,
        cub->texture->no_path, &cub->texture->no_img.width, &cub->texture->no_img.height);
    if (!cub->texture->no_img.img)
    {
        perror("Failed to load north texture");
        exit(1);
    }
    cub->texture->no_img.addr = mlx_get_data_addr(cub->texture->no_img.img,
        &cub->texture->no_img.bits_per_pixel, &cub->texture->no_img.line_length,
        &cub->texture->no_img.endian);

    cub->texture->so_img.img = mlx_xpm_file_to_image(cub->data.mlx,
        cub->texture->so_path, &cub->texture->so_img.width, &cub->texture->so_img.height);
    if (!cub->texture->so_img.img)
        perror("Failed to load south texture");
    cub->texture->so_img.addr = mlx_get_data_addr(cub->texture->so_img.img,
        &cub->texture->so_img.bits_per_pixel, &cub->texture->so_img.line_length,
        &cub->texture->so_img.endian);

    cub->texture->we_img.img = mlx_xpm_file_to_image(cub->data.mlx,
        cub->texture->we_path, &cub->texture->we_img.width, &cub->texture->we_img.height);
    if (!cub->texture->we_img.img)
        perror("Failed to load west texture");
    cub->texture->we_img.addr = mlx_get_data_addr(cub->texture->we_img.img,
        &cub->texture->we_img.bits_per_pixel, &cub->texture->we_img.line_length,
        &cub->texture->we_img.endian);

    cub->texture->ea_img.img = mlx_xpm_file_to_image(cub->data.mlx,
        cub->texture->ea_path, &cub->texture->ea_img.width, &cub->texture->ea_img.height);
    if (!cub->texture->ea_img.img)
        perror("Failed to load east texture");
    cub->texture->ea_img.addr = mlx_get_data_addr(cub->texture->ea_img.img,
        &cub->texture->ea_img.bits_per_pixel, &cub->texture->ea_img.line_length,
        &cub->texture->ea_img.endian);
}
void init_texture_door(t_cub *cub)
{
    cub->texture->door_img.img = mlx_xpm_file_to_image(cub->data.mlx,
        "./textures/door/door.xpm", &cub->texture->door_img.width, &cub->texture->door_img.height);
    if (!cub->texture->door_img.img)
    {
        ft_putendl_fd("Error\nFailed to load door texture", 2);
        exit(1);
    }
    cub->texture->door_img.addr = mlx_get_data_addr(cub->texture->door_img.img,
        &cub->texture->door_img.bits_per_pixel, &cub->texture->door_img.line_length,
        &cub->texture->door_img.endian);
}


void init_texture_door_anim(t_cub *cub)
{
    char *door_paths[MAX_DOOR_FRAMES] = {
        "./textures/door/__door1.xpm",
        "./textures/door/__door2.xpm",
        "./textures/door/door_01.xpm",
        "./textures/door/__door2.xpm"
    };

    for (int i = 0; i < MAX_DOOR_FRAMES; i++)
    {
        cub->door_textures[i].img = mlx_xpm_file_to_image(cub->data.mlx,
            door_paths[i], &cub->door_textures[i].width, &cub->door_textures[i].height);
        if (!cub->door_textures[i].img)
        {
            ft_putendl_fd("Error loading door animation texture", 2);
            while (--i >= 0)
                mlx_destroy_image(cub->data.mlx, cub->door_textures[i].img);
            exit(EXIT_FAILURE);
        }
        cub->door_textures[i].addr = mlx_get_data_addr(cub->door_textures[i].img,
            &cub->door_textures[i].bits_per_pixel, &cub->door_textures[i].line_length,
            &cub->door_textures[i].endian);
    }

    cub->door_anim_active = 0;
    cub->door_anim_frame = 0;
    cub->door_anim_tick = 0;
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
    init_texture_wall(cub);
    init_texture_door(cub);
    init_texture_door_anim(cub);
	if (event_hook_window(cub))
        return (1);
	return (0);
}	