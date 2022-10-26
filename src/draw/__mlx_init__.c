#include "../../includes/cub3d.h"


int close_window(t_map_data *ptr)
{
	exit(0);
	return (0);
}

int mouse_move_hook(int x, int y, t_map_data *ptr)
{
	ptr->img->mouse_x = x;
	ptr->img->mouse_y = y;
	return (0);
}

/// ---------------------------- mlx_warper ---------------------------- ///



int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


int key_press(int keycode, t_map_data *ptr)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(ptr->img->mlx, ptr->img->mlx_win);
		close_window(ptr);
	}
	if (keycode == LEFT)
		ptr->p_angle -= ROTATION_SPEED;
	else if (keycode == RIGHT)
		ptr -> p_angle += ROTATION_SPEED;

	ptr->img->key_press = keycode;
	return (0);
}

int key_release(int keycode, t_map_data *ptr)
{
	ptr->img->key_release = keycode;
	return (0);
}

void	my_mlx_pixel_put(t_map_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img->addr + (y * data->img->line_length + x * (data->img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void get_distance(t_map_data *ptr)
{
	float y = 2.5;
	float x = 3.5;

	float angle = ptr->p_angle - (FIELD_OF_VIEW / 2);
	int i = 0;
	while (i < WIDTH)
	{
		while (ptr->map[(int)y][(int)x] != '1')
		{
			x += cos(angle);
			y += sin(angle);
		}
		ptr->dists[i] = hypot(x - 3.5, y - 2.5);
		y = 2.5;
		x = 3.5;
		printf("%f\n", ptr->dists[i]);
		
		i++;
		angle += (FIELD_OF_VIEW / WIDTH);
	}
}

int	render_next_frame(t_map_data *ptr)
{
	int x = -1;
	int y;

	get_distance(ptr);
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			my_mlx_pixel_put(ptr, x, y, create_trgb(250,250,250, 255)); // <- to be changed
		}
	}
	mlx_put_image_to_window(ptr->img->mlx, ptr->img->mlx_win, ptr->img->img, 0, 0);
	return (1);
}

void window_init(t_map_data *scrape)
{
    t_mlx_img *ptr;
	
	ptr = malloc(sizeof(t_mlx_img));
	if (!ptr)
		return ;
	scrape->dists = ft_calloc(sizeof(float), WIDTH);
	scrape->p_angle = M_PI / 6;
	scrape->img = ptr;
	
	ptr->mlx = mlx_init();
	ptr->mlx_win = mlx_new_window(ptr->mlx, WIDTH, HEIGHT, "cub3D");
	ptr->img = mlx_new_image(ptr->mlx, WIDTH, HEIGHT);
	ptr->addr = mlx_get_data_addr(ptr->img, &ptr->bits_per_pixel, &ptr->line_length, &ptr->endian);

	
	mlx_hook(ptr->mlx_win,2, 0, key_press, scrape);
	mlx_hook(ptr->mlx_win,3, 0, key_release,scrape);
	mlx_hook(ptr->mlx_win,6, 0, mouse_move_hook, scrape);
	mlx_hook(ptr->mlx_win,17, 0, close_window, scrape);

	
	mlx_loop_hook(ptr->mlx, render_next_frame, scrape);
	mlx_loop(ptr->mlx);
}


void mlx_warper(t_map_data *scrape)
{
    window_init(scrape);
	
}