/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:15:15 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/01 17:08:59 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int palyer_chars(char c)
{
	return (c == 'W' || c == 'S' || c == 'E' || c == 'N');
}

int valid_chars(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'W' || c == 'S' || c == 'E' || c == 'N' || c == '2');
}

void reset_texture(t_texture *textur)
{
	textur->cn = 0;
	textur->no = 0;
	textur->ea = 0;
	textur->fn = 0;
	textur->so = 0;
	textur->we = 0;
}

int only_walls_map(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != '1')
			return (0);
		s++;
	}
	return (1);
}

int check_chars(char *s)
{
	int i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (!valid_chars(s[i]))
		{
			s[i + 1] = '\0';
			log_state(ft_strjoin("INVALID CHAR : ", s + i), 0);
		}
		i++;
	}
	return (0);
}

int check_walls(char **map)
{
	int y;
	int x;

	y = 0;
	while (map[y])
	{
		log_state(ft_strjoin("CHECKING LINE > ", map[y]), 3);
		x = 0;
		if (check_chars(map[y]))
			return (1);
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				if (!map[y][x + 1] || !map[y][x - 1] || !map[y + 1][x] || !map[y + 1][x])
					log_state("Player will be out of the map", 0);
			}
			x++;
		}
		log_state("VALID LINE", 1);
		y++;
	}
	return (0);
}

int only_ones(char *line)
{
	int i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int check_map(t_cub *cub)
{
	char **map;
	int count;
	int i;
	int j;

	i = 0;
	count = 0;
	map = cub->data.map.map;
	log_state("MAP CHECKING", 3);
	if (!map)
		return (log_state("Thers is no map", 0), 1);
	if (only_ones(map[0]))
		log_state(ft_strjoin("Unclosed wall Line : ", map[i]), 0);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (count > 1)
				return (log_state("Multiple players Dedected", 0), 1);
			if (palyer_chars(map[i][j]))
				count++;
			j++;
		}
		if (!map[i + 1] && only_ones(map[i]))
			log_state(ft_strjoin("Unclosed wall Line : ", map[i]), 0);
		i++;
	}
	if (!count)
		return (log_state("The map has no player", 0), 1);
	return (check_walls(map));
}
