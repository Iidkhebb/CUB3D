#include "../../includes/cub3d.h"

void window_init()
{
    void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "CUB3D");
	mlx_loop(mlx);
}


void mlx_warper()
{
    window_init();
}