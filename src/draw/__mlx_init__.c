#include "../../includes/cub3d.h"


int close_window(t_map_data *ptr)
{
	exit(0);
	return (0);
}
int mouse_hook(int button,	t_map_data *ptr)
{
	// printf("Hello from mouse_hook! -> %d \n", button);
	ptr->img->mouse_hook = button;
	return (0);
}

int mouse_move_hook(int x, int y, t_map_data *ptr)
{
	ptr->img->mouse_x = x;
	ptr->img->mouse_y = y;
	return (0);
}

/// ---------------------------- mlx_warper ---------------------------- ///


void	my_mlx_pixel_put(t_map_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img->addr + (y * data->img->line_length + x * (data->img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	render_next_frame(t_map_data *ptr)
{
	int x = -1;
	int y;

	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			my_mlx_pixel_put(ptr, x, y, create_trgb(ptr->img->mouse_x, ptr->img->mouse_x, 100, 0)); // <- to be changed
		}
	}
	return (mlx_put_image_to_window(ptr->img->mlx, ptr->img->mlx_win, ptr->img->img, 0, 0));
}

int key_press(int keycode, t_map_data *ptr)
{
	if (keycode == 53)
	{
		mlx_destroy_window(ptr->img->mlx, ptr->img->mlx_win);
		close_window(ptr);
	}
	ptr->img->mouse_x = 0;
	return (0);
}

int key_release(int keycode, t_map_data *ptr)
{
	ptr->img->mouse_x = keycode * 10;
	return (0);
}

void window_init(t_map_data *scrape)
{
    t_mlx_img *ptr;
	
	ptr = malloc(sizeof(t_mlx_img));
	if (!ptr)
		return ;
	scrape->img = ptr;
	ptr->mlx = mlx_init();
	ptr->mlx_win = mlx_new_window(ptr->mlx, WIDTH, HEIGHT, "cub3D");
	ptr->img = mlx_new_image(ptr->mlx, WIDTH, HEIGHT);
	ptr->addr = mlx_get_data_addr(ptr->img, &ptr->bits_per_pixel, &ptr->line_length, &ptr->endian);

	
	mlx_hook(ptr->mlx_win,2, 0, key_press, scrape);
	mlx_hook(ptr->mlx_win,3, 0, key_release,scrape);
	mlx_hook(ptr->mlx_win,6, 0, mouse_move_hook, scrape);
	mlx_mouse_hook(ptr->mlx_win, mouse_hook, scrape);
	mlx_hook(ptr->mlx_win,17, 0, close_window, scrape);

	
	mlx_loop_hook(ptr->mlx, render_next_frame, scrape);
	mlx_loop(ptr->mlx);
}


void mlx_warper(t_map_data *scrape)
{
    window_init(scrape);
	
}