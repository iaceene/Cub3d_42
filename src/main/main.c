/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:43:09 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/02 17:59:01 by yaajagro         ###   ########.fr       */
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

	printf(COLOR_YELLOW "[INIT PARSING] " COLOR_RESET "\n");
	if (map_parsing(ac, av, &cub))
		return (clean_up(), 1);
	printf(COLOR_GREEN  "[DONE PARSING] " COLOR_RESET "\n");
	printf(COLOR_YELLOW   "[CREATING WINDOW]  " COLOR_RESET "\n");
	if (init_window(&cub))
		return (clean_up(), 1);
	clean_up();
	return (0);
}
