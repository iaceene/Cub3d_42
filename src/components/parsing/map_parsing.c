/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:38:14 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/29 19:23:32 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*read_map(int fd)
{
	char	*map;
	char	*buffer;

	map = NULL;
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		map = ft_strjoin(map, buffer);
	}
	return (map);
}

int	check_file_extention(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str == '.')
		{
			str++;
			if (ft_strncmp(str, "cub", 3) == 0 && str[3] == '\0')
				return (0);
			else
				return (1);
		}
		str++;
	}
	return (1);
}

int	init_map(t_cub *cub, char *filename)
{
	int	fd;

	if (check_file_extention(filename))
		return (ft_putendl_fd("Error\nInvalid Extention", 2), 1);
	fd = open(filename,	0);
	if (fd == -1)
		return (ft_putendl_fd("Error\nFailed to open map file", 2), 1);
	cub->data.map.map = ft_split(read_map(fd), '\n');
	if (!cub->data.map.map)
		return (ft_putendl_fd("Error\nFailed to read map", 2), 1);
	close(fd);
	return (0);
}

t_lines	*new_line(char *val)
{
	t_lines	*new;

	new = ft_malloc(sizeof(t_lines));
	new->next = NULL;
	new->val = val;
	return (new);
}

void	ft_add_line(t_lines **head, t_lines *new)
{
	t_lines	*last;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

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

t_lines	*map_extracter(t_lines *line, char ***map)
{
	int 	len;
	char	**new;
	int		i;

	len = get_map_len(line);
	i = 0;
	*map = ft_malloc((sizeof(char *) * len) + 1);
	new = *map;
	while (line && !is_same(line->val, "MAP END"))
	{
		if (!is_same(line->val, "MAP BEGIN"))
		{
			new[i] = line->val;
			i++;
		}
		line = line->next;
	}
	new[i] = NULL;
	return (line);
}

int	extractor(t_cub *cub)
{
	t_lines		*line;
	t_texture	*textur;

	textur = ft_malloc(sizeof(t_texture));
	cub->texture = textur;
	line = cub->data.lines;
	if (!line)
		return (1);
	line = textures_extracter(line, textur);
	if (!line)
		return (ft_putendl_fd("Error\n No map Found", 2), 1);
	line = map_extracter(line, &cub->data.map.map);
	if (!line)
		return (ft_putendl_fd("Error", 2), 1);
	return (0);
}

int	check_file(char *filename)
{
	int	fd;
	
	if (!filename)
		return (ft_putendl_fd("Error\nTextur not found", 2), 1);
	fd = open(filename, 0);
	if (fd == -1)
	{
		perror(filename);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_texture(t_cub *cub)
{
	t_texture *texture;

	texture = cub->texture;
	if (check_file(texture->ea_path) || check_file(texture->so_path)
	|| check_file(texture->we_path) || check_file(texture->no_path))
		return (1);
	return (0);
}

int	check_colors(t_cub *cub)
{
	t_texture *texture;

	texture = cub->texture;
	if (!texture->floor_clr || !texture->sky_clr)
	{
		if (!texture->floor_clr && texture->sky_clr)
			ft_putendl_fd("Error\nFloor color not found", 2);
		else if (!texture->sky_clr && texture->floor_clr)
			ft_putendl_fd("Error\nsky color not found", 2);
		else
			ft_putendl_fd("Error\ncolors not found", 2);
		return (1);
	}
	return (0);	
}

int map_parsing(int ac, char **av, t_cub *cub)
{
	if (ac != 2)
		return (ft_putendl_fd("Error\nUsage: ./cub3D <map.cub>", 2), 1);
	if (init_map(cub, av[1]))
		return (ft_putendl_fd("Error\nFailed to initialize map", 2), 1);
	if (parse_lines(cub))
		return (ft_putendl_fd("Error\nFailed to parse lines", 2), 1);
	if (extractor(cub))
		return (1);
	// if (check_texture(cub) || check_colors(cub)
	// 	|| check_map(cub))
	if (check_colors(cub))
		return (1);
	return (0);
}
