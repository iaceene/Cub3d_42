#include "../include/cub3d.h"

int main()
{
	void    *mlx;
	void    *win;

	mlx = mlx_init();
	if (!mlx)
		return (1);

	win = mlx_new_window(mlx, 800, 600, "Simple Window");
	if (!win)
		return (1);

	mlx_loop(mlx);
	return (0);
}