/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_7.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:18:13 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/18 18:42:27 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_rendring_depend(t_cub *cub)
{
	char	*door_path;
	int		fd;

	door_path = "./textures/door/__door1.xpm";
	if (!cub)
		return ;
	log_state("CHECKING DEPENDENCIES", 3);
	fd = open(door_path, 0);
	if (fd == -1)
		log_state("DOOR IMG NOT FOUND", 0);
	close(fd);
	log_state("CHECKING DEPENDENCIES", 1);
}

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
