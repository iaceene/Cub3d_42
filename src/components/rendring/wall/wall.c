/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:04:40 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/31 15:07:09 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	load_north_texture(t_cub *cub)
{
	cub->texture->no_img.img = mlx_xpm_file_to_image(cub->data.mlx,
			cub->texture->no_path, &cub->texture->no_img.width,
			&cub->texture->no_img.height);
	if (!cub->texture->no_img.img)
	{
		perror("Failed to load north texture");
		exit(1);
	}
	cub->texture->no_img.addr = mlx_get_data_addr(cub->texture->no_img.img,
			&cub->texture->no_img.bits_per_pixel,
			&cub->texture->no_img.line_length,
			&cub->texture->no_img.endian);
}

static void	load_south_texture(t_cub *cub)
{
	cub->texture->so_img.img = mlx_xpm_file_to_image(cub->data.mlx,
			cub->texture->so_path, &cub->texture->so_img.width,
			&cub->texture->so_img.height);
	if (!cub->texture->so_img.img)
		perror("Failed to load south texture");
	cub->texture->so_img.addr = mlx_get_data_addr(cub->texture->so_img.img,
			&cub->texture->so_img.bits_per_pixel,
			&cub->texture->so_img.line_length,
			&cub->texture->so_img.endian);
}

static void	load_west_texture(t_cub *cub)
{
	cub->texture->we_img.img = mlx_xpm_file_to_image(cub->data.mlx,
			cub->texture->we_path, &cub->texture->we_img.width,
			&cub->texture->we_img.height);
	if (!cub->texture->we_img.img)
		perror("Failed to load west texture");
	cub->texture->we_img.addr = mlx_get_data_addr(cub->texture->we_img.img,
			&cub->texture->we_img.bits_per_pixel,
			&cub->texture->we_img.line_length,
			&cub->texture->we_img.endian);
}

static void	load_east_texture(t_cub *cub)
{
	cub->texture->ea_img.img = mlx_xpm_file_to_image(cub->data.mlx,
			cub->texture->ea_path, &cub->texture->ea_img.width,
			&cub->texture->ea_img.height);
	if (!cub->texture->ea_img.img)
		perror("Failed to load east texture");
	cub->texture->ea_img.addr = mlx_get_data_addr(cub->texture->ea_img.img,
			&cub->texture->ea_img.bits_per_pixel,
			&cub->texture->ea_img.line_length,
			&cub->texture->ea_img.endian);
}

void	init_texture_wall(t_cub *cub)
{
	load_north_texture(cub);
	load_south_texture(cub);
	load_west_texture(cub);
	load_east_texture(cub);
}
