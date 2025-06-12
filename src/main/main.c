/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:43:09 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/07 17:42:07 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_up(void)
{
	ft_malloc(-1);
}

int main(int ac, char **av)
{
	t_cub cub;

	log_state("INIT PARSING", 3);
	if (map_parsing(ac, av, &cub))
		return (clean_up(), 1);
	log_state("PARSING DONE", 1);
	clean_up();
	return (0);
}
