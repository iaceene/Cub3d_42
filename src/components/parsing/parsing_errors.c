/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:03:29 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/13 21:03:32 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	exit_cub(void)
{
	write(1, COLOR_RED, ft_strlen(COLOR_RED));
	write(1, " ]\n", 4);
	write(1, "[ 🚧 EXITING ]\n", 18);
	write(1, COLOR_RESET, ft_strlen(COLOR_RESET));
	ft_malloc(-1);
	exit(1);
}

static void	print_log_prefix(int fd, int flag)
{
	if (fd == 2)
		write(2, "[ Error ]\n", 10);
	if (flag == 1)
		write(fd, "[ ✅ ", 7);
	else if (flag == 3)
		write(fd, "[ ⏳ ", 7);
	else
		write(fd, "[ ⛔ ", 7);
}

static void	print_log_message(char *msg, int fd)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(fd, &msg[i], 1);
		i++;
	}
}

void	log_state(char *msg, int flag)
{
	int		fd;
	char	*clr;

	if (!msg)
		return ;
	fd = 1;
	clr = COLOR_GREEN;
	if (!flag)
	{
		fd = 2;
		clr = COLOR_RED;
	}
	else if (flag == 3)
		clr = COLOR_YELLOW;
	write(fd, clr, ft_strlen(clr));
	print_log_prefix(fd, flag);
	print_log_message(msg, fd);
	if (fd == 2)
		exit_cub();
	else
		write(fd, " ]\n", 3);
	write(fd, COLOR_RESET, ft_strlen(COLOR_RESET));
}
