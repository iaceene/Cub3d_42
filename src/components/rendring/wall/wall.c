/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:04:40 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/17 23:03:03 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static int load_north_texture(t_cub *cub)
{
	cub->texture->no_img.img = mlx_xpm_file_to_image(cub->data.mlx,
													 cub->texture->no_path, &cub->texture->no_img.width,
													 &cub->texture->no_img.height);
	if (!cub->texture->no_img.img)
		return (1);
	cub->texture->no_img.addr = mlx_get_data_addr(cub->texture->no_img.img,
												  &cub->texture->no_img.bits_per_pixel,
												  &cub->texture->no_img.line_length,
												  &cub->texture->no_img.endian);
	return (0);
}

static int load_south_texture(t_cub *cub)
{
	cub->texture->so_img.img = mlx_xpm_file_to_image(cub->data.mlx,
													 cub->texture->so_path, &cub->texture->so_img.width,
													 &cub->texture->so_img.height);
	if (!cub->texture->so_img.img)
		return (1);
	cub->texture->so_img.addr = mlx_get_data_addr(cub->texture->so_img.img,
												  &cub->texture->so_img.bits_per_pixel,
												  &cub->texture->so_img.line_length,
												  &cub->texture->so_img.endian);
	return (0);
}

static int load_west_texture(t_cub *cub)
{
	cub->texture->we_img.img = mlx_xpm_file_to_image(cub->data.mlx,
													 cub->texture->we_path, &cub->texture->we_img.width,
													 &cub->texture->we_img.height);
	if (!cub->texture->we_img.img)
		return (1);
	cub->texture->we_img.addr = mlx_get_data_addr(cub->texture->we_img.img,
												  &cub->texture->we_img.bits_per_pixel,
												  &cub->texture->we_img.line_length,
												  &cub->texture->we_img.endian);
	return (0);
}

static int load_east_texture(t_cub *cub)
{
	cub->texture->ea_img.img = mlx_xpm_file_to_image(cub->data.mlx,
													 cub->texture->ea_path, &cub->texture->ea_img.width,
													 &cub->texture->ea_img.height);
	if (!cub->texture->ea_img.img)
		return (1);
	cub->texture->ea_img.addr = mlx_get_data_addr(cub->texture->ea_img.img,
												  &cub->texture->ea_img.bits_per_pixel,
												  &cub->texture->ea_img.line_length,
												  &cub->texture->ea_img.endian);
	return (0);
}

void destroy_imgs_exit(t_cub *cub, char *msg)
{
	if (cub->texture->door_img.img)
		mlx_destroy_image(cub->data.mlx, cub->texture->door_img.img);
	if (cub->texture->ea_img.img)
		mlx_destroy_image(cub->data.mlx, cub->texture->ea_img.img);
	if (cub->texture->we_img.img)
		mlx_destroy_image(cub->data.mlx, cub->texture->we_img.img);
	if (cub->texture->no_img.img)
		mlx_destroy_image(cub->data.mlx, cub->texture->no_img.img);
	if (cub->texture->so_img.img)
		mlx_destroy_image(cub->data.mlx, cub->texture->so_img.img);
	if (cub->data.img.img)
		mlx_destroy_image(cub->data.mlx, cub->data.img.img);
	int i = 0;
	while (i < 18)
	{
		if (cub->texture->weapon[i].img)
			mlx_destroy_image(cub->data.mlx, cub->texture->weapon[i].img);
		i++;
	}
	mlx_destroy_window(cub->data.mlx, cub->data.win);
	mlx_destroy_display(cub->data.mlx);
	free(cub->data.mlx);
	if (msg)
		log_state(msg, 0);
	log_state("CLEANING...", 1);
	ft_malloc(-1);
	printf("[ BYE ! ]\n");
	exit(0);
}

void init_texture_wall(t_cub *cub)
{
	if (load_north_texture(cub) || load_south_texture(cub) || load_west_texture(cub) || load_east_texture(cub))
		destroy_imgs_exit(cub, "FAILED TO LOAD A WALL TEXTURE");
}
