#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_mlx_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	render_next_frame(t_mlx_img *ptr)
{
	int x = -1;
	int y;
	static int rand = 10;

	while (++x < 1280)
	{
		y = -1;
		while (++y < 720)
		{
			my_mlx_pixel_put(ptr, x, y, ((create_trgb(rand, rand, 1, 0) )));
		}
	}
	rand += 1;
	return (mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->img, 0, 0));
}

void window_init(t_map_data *scrape)
{
    t_mlx_img *ptr;
	
	ptr = malloc(sizeof(t_mlx_img));
	
	ptr->mlx = mlx_init();
	ptr->mlx_win = mlx_new_window(ptr->mlx, 1280, 720, "cub3D");
	ptr->img = mlx_new_image(ptr->mlx, 1280, 720);
	ptr->addr = mlx_get_data_addr(ptr->img, &ptr->bits_per_pixel, &ptr->line_length, &ptr->endian);


	mlx_loop_hook(ptr->mlx, render_next_frame, ptr);
	mlx_loop(ptr->mlx);
}


void mlx_warper(t_map_data *scrape)
{
    window_init(scrape);
	
}