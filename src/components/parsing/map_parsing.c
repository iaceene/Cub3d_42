/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:38:14 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/04 17:21:04 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_len(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	check_grb_rang(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (cub->texture->sky_grb[i] == -1
			|| cub->texture->floor_grb[i] == -1)
			return (log_state("Invalid RGB range", 0), 1);
		i++;
	}
	return (0);
}

int	check_rgb(t_cub *cub)
{
	char	**clr1;
	char	**clr2;
	int		i;

	i = 0;
	if (check_comas(cub->texture->sky_clr, cub->texture->floor_clr))
		return (1);
	clr1 = ft_split(cub->texture->floor_clr, ',');
	clr2 = ft_split(cub->texture->sky_clr, ',');
	if (!clr1 || !clr2
		|| get_len(clr1) != 3 || get_len(clr2) != 3)
		return (log_state("Invalid color format", 0), 1);
	while (i < 3)
	{
		cub->texture->floor_grb[i] = ft_atoi(clr1[i]);
		cub->texture->sky_grb[i] = ft_atoi(clr2[i]);
		i++;
	}
	return (check_grb_rang(cub));
}

int	check_colors(t_cub *cub)
{
	t_texture	*texture;

	texture = cub->texture;
	if (!texture->floor_clr || !texture->sky_clr)
	{
		if (!texture->floor_clr && texture->sky_clr)
			log_state("Floor color not found", 0);
		else if (!texture->sky_clr && texture->floor_clr)
			log_state("Sky color not found", 0);
		else
			log_state("colors not found", 0);
		return (1);
	}
	return (check_rgb(cub));
}

void set_map_size(t_cub *cub)
{
	char		**map;
	size_t		x;
	int			y;

	if (!cub)
		return ;
	map = cub->data.map.map;
	x = 0;
	y = 0;
	while (map[y])
	{
		if (ft_strlen(map[y]) > x)
			x = ft_strlen(map[y]);
		y++;
	}
	cub->data.map.width = (int)x;
	cub->data.map.height = y;
}

int	map_parsing(int ac, char **av, t_cub *cub)
{
	if (ac != 2)
		return (log_state("Usage: ./cub3D \"map.cub\"", 0), 1);
	if (init_map(cub, av[1]))
		return (log_state("Failed to initialize map", 0), 1);
	if (parse_lines(cub))
		return (log_state("Failed to parse lines", 0), 1);
	if (extractor(cub))
		return (1);
	// if (check_texture(cub) || check_colors(cub)
	if (check_colors(cub)
		|| check_map(cub))
		return (1);
	set_map_size(cub);
	return (0);
}
