#include "../../includes/cub3d.h"


int close_window(t_mlx_img *ptr)
{
	exit(0);
	return (0);
}
int mouse_hook(int button,  t_mlx_img *ptr)
{
	// printf("Hello from mouse_hook! -> %d \n", button);
	return (0);
}

int mouse_move_hook(int x, int y, t_mlx_img *ptr)
{
	ptr->mouse_x = 0;
	ptr->mouse_y = 0;
	return (0);
}

/// ---------------------------- mlx_warper ---------------------------- ///


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

	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			my_mlx_pixel_put(ptr, x, y, create_trgb(ptr->mouse_x, ptr->mouse_x, 100, 0));
		}
	}
	return (mlx_put_image_to_window(ptr->mlx, ptr->mlx_win, ptr->img, 0, 0));
}

int key_press(int keycode, t_mlx_img *ptr)
{
	if (keycode == 53)
	{
		mlx_destroy_window(ptr->mlx, ptr->mlx_win);
		close_window(ptr);
	}
	ptr->mouse_x = 0;
	printf("keycode press: %d\n", keycode);
	return (0);
}

int key_release(int keycode, t_mlx_img *ptr)
{
	ptr->mouse_x = keycode * 10;
	printf("keycode release: %d\n", keycode);
	return (0);
}

void window_init(t_map_data *scrape)
{
    t_mlx_img *ptr;
	
	ptr = malloc(sizeof(t_mlx_img));
	
	ptr->mlx = mlx_init();
	ptr->mlx_win = mlx_new_window(ptr->mlx, WIDTH, HEIGHT, "cub3D");
	ptr->img = mlx_new_image(ptr->mlx, WIDTH, HEIGHT);
	ptr->addr = mlx_get_data_addr(ptr->img, &ptr->bits_per_pixel, &ptr->line_length, &ptr->endian);

	
	mlx_hook(ptr->mlx_win,2, 0, key_press, ptr);
	mlx_hook(ptr->mlx_win,3, 0, key_release, ptr);
	mlx_hook(ptr->mlx_win,6, 0, mouse_move_hook, ptr);
	mlx_mouse_hook(ptr->mlx_win, mouse_hook, ptr);
	mlx_hook(ptr->mlx_win,17, 0, close_window, ptr);

	
	mlx_loop_hook(ptr->mlx, render_next_frame, ptr);
	mlx_loop(ptr->mlx);
}


void mlx_warper(t_map_data *scrape)
{
    window_init(scrape);
	
}