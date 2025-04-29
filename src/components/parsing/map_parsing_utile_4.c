/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:15:15 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/29 21:46:45 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	palyer_chars(char c)
{
	return (c == 'W' || c == 'S' || c == 'E'
		|| c == 'N');
}

int	check_map(t_cub *cub)
{
	char	**map;
	int		count;
	int		i;
	int		j;

	i = 0;
	count = 0;
	map = cub->data.map.map;
	if (!map)
		return (1);
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
			return (ft_putendl_fd("Error\nUnclosed wall Dedected", 2), 1);
		j = 0;
		while (map[i][j])
		{
			if (count > 1)
				return (ft_putendl_fd("Error\nMultiple players Dedected", 2) ,1);
			if (palyer_chars(map[i][j]))
				count++;
			j++;	
		}
		i++;
	}
	return (0);	
}
