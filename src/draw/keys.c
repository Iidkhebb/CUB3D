#include "../../includes/cub3d.h"

int key_press(int keycode, t_map_data *ptr)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(ptr->img->mlx, ptr->img->mlx_win);
		close_window(ptr);
	}
	if(keycode == ESPACE)
		ptr->is_open = 1;
	if (keycode == W)
		ptr->is_pressed_w = 1;
	if (keycode == S)
		ptr->is_pressed_s = 1;
	if (keycode == A)
		ptr->is_pressed_a = 1;
	if (keycode == D)
		ptr->is_pressed_d = 1;
	if (keycode == LEFT)
		ptr->is_pressed_left = 1;
	if (keycode == RIGHT)
		ptr->is_pressed_right = 1;
	return (0);
}

int key_release(int keycode, t_map_data *ptr)
{
	ptr->img->key_release = keycode;
	if (keycode == ESPACE)
		ptr->is_open = 0;
	if (keycode == W)
		ptr->is_pressed_w = 0;
	if (keycode == S)
		ptr->is_pressed_s = 0;
	if (keycode == A)
		ptr->is_pressed_a = 0;
	if (keycode == D)
		ptr->is_pressed_d = 0;
	if (keycode == LEFT)
		ptr->is_pressed_left = 0;
	if (keycode == RIGHT)
		ptr->is_pressed_right = 0;
	return (0);
}

void	my_mlx_pixel_put(t_map_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img->addr + (y * data->img->line_length + x * (data->img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void _d_mouvemenst_sides(t_map_data *ptr)
{
	if (ptr->is_pressed_d)
	{
		if (ptr->map[(int)(ptr->posx + ptr->dirY * 0.5)][(int)(ptr->posy)] == '0')
			ptr->posx += ptr->dirY * SPEED;
		if (ptr->map[(int)(ptr->posx)][(int)(ptr->posy - ptr->dirx * 1)] == '0')
			ptr->posy -= ptr->dirx * SPEED;
	}
	if (ptr->is_pressed_left)
	{
		ptr->dirx = ptr->dirx * cos(0.05) - ptr->dirY * sin(0.05);
		ptr->dirY = ptr->dirx * sin(0.05) + ptr->dirY * cos(0.05);
		ptr->planex = ptr->planex * cos(0.05) - ptr->planey * sin(0.05);
		ptr->planey = ptr->planex * sin(0.05) + ptr->planey * cos(0.05);
	}
	if (ptr->is_pressed_right)
	{
		ptr->dirx = ptr->dirx * cos(-0.05) - ptr->dirY * sin(-0.05);
		ptr->dirY = ptr->dirx * sin(-0.05) + ptr->dirY * cos(-0.05);
		ptr->planex = ptr->planex * cos(-0.05) - ptr->planey * sin(-0.05);
		ptr->planey = ptr->planex * sin(-0.05) + ptr->planey * cos(-0.05);
	}
}


void _d_mouvements(t_map_data *ptr)
{
	if (ptr->is_pressed_w)
	{
		if (ptr->map[(int)(ptr->posx + ptr->dirx * 0.5)][(int)(ptr->posy)] == '0')
			ptr->posx += ptr->dirx * SPEED;
		if (ptr->map[(int)(ptr->posx)][(int)(ptr->posy + ptr->dirY * 1)] == '0')
			ptr->posy += ptr->dirY * SPEED;
	}
	if (ptr->is_pressed_s)
	{
		if (ptr->map[(int)(ptr->posx - ptr->dirx * 0.5)][(int)(ptr->posy)] == '0')
			ptr->posx -= ptr->dirx * SPEED;
		if (ptr->map[(int)(ptr->posx)][(int)(ptr->posy - ptr->dirY * 1)] == '0')
			ptr->posy -= ptr->dirY * SPEED;
	}
	if (ptr->is_pressed_a)
	{
		if (ptr->map[(int)(ptr->posx - ptr->dirY * 0.5)][(int)(ptr->posy)] == '0')
			ptr->posx -= ptr->dirY * SPEED;
		if (ptr->map[(int)(ptr->posx)][(int)(ptr->posy + ptr->dirx * 1)] == '0')
			ptr->posy += ptr->dirx * SPEED;
	}
	_d_mouvemenst_sides(ptr);
}