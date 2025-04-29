/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:01:07 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/29 21:02:46 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	valid_chars(char c)
{
	return (c == ' ' || c == '0' || c == '1'
		|| c == 'W' || c == 'S' || c == 'E'
		|| c == 'N');
}

int	only_walls(char *line)
{
	if (!line)
		return (0);
	while (*line)
	{
		if (!valid_chars(*line))
			return (0);
		line++;
	}
	return (1);
}

int	parse_lines(t_cub *cub)
{
	char		**map;
	static int	n;
	t_lines		*line;
	int			i;

	map = cub->data.map.map;
	line = NULL;
	i = 0;
	while (map[i])
	{
		if (!i)
			ft_add_line(&line, new_line(ft_strdup("TEXTUR BEGIN")));
		if (only_walls(map[i]) && !n)
		{
			ft_add_line(&line, new_line(ft_strdup("MAP BEGIN")));
			ft_add_line(&line, new_line(map[i]));	
			n++;
		}
		else
			ft_add_line(&line, new_line(map[i]));
		if (!map[i + 1])
			ft_add_line(&line, new_line(ft_strdup("MAP END")));
		i++;
	}
	cub->data.lines = line;
	return (0);
}

t_lines	*textures_extracter(t_lines *line, t_texture *textur)
{
	while (line && line->next && !is_same(line->val, "MAP BEGIN"))
	{
		if (!is_same(line->val, "TEXTUR BEGIN"))
		{
			if (!ft_strncmp(line->val, "NO ", ft_strlen("NO ")))
				textur->no_path = ft_split(line->val, ' ')[1];
			else if (!ft_strncmp(line->val, "SO ", ft_strlen("SO ")))
				textur->so_path = ft_split(line->val, ' ')[1];
			else if (!ft_strncmp(line->val, "WE ", ft_strlen("WE ")))
				textur->we_path = ft_split(line->val, ' ')[1];
			else if (!ft_strncmp(line->val, "EA ", ft_strlen("EA ")))
				textur->ea_path = ft_split(line->val, ' ')[1];
			else if (!ft_strncmp(line->val, "F ", ft_strlen("F ")))
				textur->floor_clr = ft_split(line->val, ' ')[1];
			else if (!ft_strncmp(line->val, "C ", ft_strlen("C ")))
				textur->sky_clr = ft_split(line->val, ' ')[1];
			else
				return (ft_putendl_fd("Error\nInvalid texture", 2), NULL);
		}
		line = line->next;
	}
	return (line);
}

int	get_map_len(t_lines *line)
{
	int	i;
	
	i = 0;
	while (line)
	{
		if (is_same(line->val, "MAP END"))
			break ;
		if (!is_same(line->val, "MAP BEGIN"))
			i++;
		line = line->next;
	}
	return (i);
}
