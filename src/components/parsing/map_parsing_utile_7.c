/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_7.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:18:13 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/16 22:58:40 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_rendring_depend(t_cub *cub)
{
	char	*door_path = "./textures/door/__door1.xpm";
	int		fd;
	
	if (!cub)
		return ;
	log_state("CHECKING DEPENDENCIES", 3);
	fd = open(door_path, 0);
	if (fd == -1)
	log_state("DOOR IMG NOT FOUND", 0);
	close(fd);
	log_state("DONE CHECKING DEPENDENCIES", 1);
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
