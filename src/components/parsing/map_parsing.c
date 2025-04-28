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
	printf("map: %s\n", map);
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
	
int map_parsing(int ac, char **av, t_cub *cub)
{
	if (ac != 2)
		return (ft_putendl_fd("Error\nUsage: ./cub3D <map.cub>", 2), 1);
	if (init_map(cub, av[1]))
		return (ft_putendl_fd("Error\nFailed to initialize map", 2), 1);
	return (0);
}