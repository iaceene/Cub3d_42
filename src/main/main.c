#include "../include/cub3d.h"

void	clean_up(void)
{
	ft_malloc(-1);
}

int main(int ac, char **av)
{
	t_cub cub;

	if (map_parsing(ac, av, &cub))
		return (clean_up(), 1);
	return (0);
}
