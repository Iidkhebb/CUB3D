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
	if (keycode == W)
	{
		ptr->is_pressed_W = 1;
	}
	if (keycode == S)
	{
		ptr->is_pressed_S = 1;
	}
	if (keycode == A)
	{
		ptr->is_pressed_A = 1;
	}
	if (keycode == D)
	{
		ptr->is_pressed_D = 1;
	}
	if (keycode == LEFT)
	{
		ptr->is_pressed_LEFT = 1;
	}
	if (keycode == RIGHT)
	{
		ptr->is_pressed_RIGHT = 1;
	}
	change_player_pos(ptr, ptr->img->key_press);
	return (0);
}

int key_release(int keycode, t_map_data *ptr)
{
	ptr->img->key_release = keycode;
	if (keycode == W)
	{
		ptr->is_pressed_W = 0;
	}
	if (keycode == S)
	{
		ptr->is_pressed_S = 0;
	}
	if (keycode == A)
	{
		ptr->is_pressed_A = 0;
	}
	if (keycode == D)
	{
		ptr->is_pressed_D = 0;
	}
	if (keycode == LEFT)
	{
		ptr->is_pressed_LEFT = 0;
	}
	if (keycode == RIGHT)
	{
		ptr->is_pressed_RIGHT = 0;
	}
	return (0);


}

void	my_mlx_pixel_put(t_map_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img->addr + (y * data->img->line_length + x * (data->img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}



int	render_next_frame(t_map_data *ptr)
{
	int x = -1;
	int y;

	if (ptr->is_pressed_W)
	{
		ptr->posX += ptr->dirX * 0.1;
		ptr->posY += ptr->dirY * 0.1;
	}
	if (ptr->is_pressed_S)
	{
		ptr->posX -= ptr->dirX * 0.1;
		ptr->posY -= ptr->dirY * 0.1;
	}
	if (ptr->is_pressed_A)
	{
		ptr->posX -= ptr->dirY * 0.1;
		ptr->posY += ptr->dirX * 0.1;
	}
	if (ptr->is_pressed_D)
	{
		ptr->posX += ptr->dirY * 0.1;
		ptr->posY -= ptr->dirX * 0.1;
	}
	if (ptr->is_pressed_LEFT)
	{
		ptr->dirX = ptr->dirX * cos(0.05) - ptr->dirY * sin(0.05);
		ptr->dirY = ptr->dirX * sin(0.05) + ptr->dirY * cos(0.05);
		ptr->planeX = ptr->planeX * cos(0.05) - ptr->planeY * sin(0.05);
		ptr->planeY = ptr->planeX * sin(0.05) + ptr->planeY * cos(0.05);
	}
	if (ptr->is_pressed_RIGHT)
	{
		ptr->dirX = ptr->dirX * cos(-0.05) - ptr->dirY * sin(-0.05);
		ptr->dirY = ptr->dirX * sin(-0.05) + ptr->dirY * cos(-0.05);
		ptr->planeX = ptr->planeX * cos(-0.05) - ptr->planeY * sin(-0.05);
		ptr->planeY = ptr->planeX * sin(-0.05) + ptr->planeY * cos(-0.05);
	}
	
	ray_casting(ptr);
	mlx_put_image_to_window(ptr->img->mlx, ptr->img->mlx_win, ptr->img->img, 0, 0);


	// mini_map(ptr);
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
    get_player_pos(scrape);
	scrape->length_line = ft_strlen(scrape->map[0]);
	window_init(scrape);
	
}