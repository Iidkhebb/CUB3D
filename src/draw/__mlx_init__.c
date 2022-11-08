#include "../../includes/cub3d.h"

int close_window(t_map_data *ptr)
{
	list_free_map(&ptr);
	exit(0);
	return (0);
}



void open_door(t_map_data *ptr, int x, int y)
{
	if (ptr->map[x][y] == 'D')
	{
		ptr->map[x][y] = '0';
	}
}

void close_door(t_map_data *ptr, int x, int y)
{
	if (ptr->map[x][y] == '0')
	{
		ptr->map[x][y] = 'D';
	}
}

int mouse_move_hook(int x, int y, t_map_data *ptr)
{
	if (x < ptr->img->mouse_x && (x <= WIDTH && x >= 0))
	{
		ptr->dirx = ptr->dirx * cos(0.02) - ptr->dirY * sin(0.02);
		ptr->dirY = ptr->dirx * sin(0.02) + ptr->dirY * cos(0.02);
		ptr->planex = ptr->planex * cos(0.02) - ptr->planey * sin(0.02);
		ptr->planey = ptr->planex * sin(0.02) + ptr->planey * cos(0.02);
		
	}
	else if (x > ptr->img->mouse_x && (x <= WIDTH && x >= 0))
	{
		ptr->dirx = ptr->dirx * cos(-0.02) - ptr->dirY * sin(-0.02);
		ptr->dirY = ptr->dirx * sin(-0.02) + ptr->dirY * cos(-0.02);
		ptr->planex = ptr->planex * cos(-0.02) - ptr->planey * sin(-0.02);
		ptr->planey = ptr->planex * sin(-0.02) + ptr->planey * cos(-0.02);
		
	}
	ptr->img->mouse_x = x;
	ptr->img->mouse_y = y;
	return (0);
}

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

void _3D_mouvemenst_sides(t_map_data *ptr)
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


void _3D_mouvements(t_map_data *ptr)
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
	_3D_mouvemenst_sides(ptr);
}

void render_torch(t_map_data *ptr)
{
	int y;
	int x;
	static int i = 5;
 	mlx_put_image_to_window(&ptr->img->mlx, ptr->img->mlx_win,ptr->tex[i].img, WIDTH / 2, HEIGHT /ptr->tex[i].img_height);
	i = (i + 1) % 10;
}

int	render_next_frame(t_map_data *ptr)
{
	_3D_mouvements(ptr);
	ray_casting(ptr);
	mini_map(ptr);
	// render_torch(ptr);
	mlx_put_image_to_window(ptr->img->mlx, ptr->img->mlx_win, ptr->img->img,0,0);
	return (1);
}

void load_texture(t_map_data *ptr, char *filename, t_textures *t)
{
	t->img = mlx_xpm_file_to_image(ptr->img->mlx, filename, &t->img_width, &t->img_height);
	if (!t->img || !filename)
		return;
	t->data = mlx_get_data_addr(t->img, &t->bpp, &t->size_line, &t->endian);
	if (! t->data || t->img_width != t->img_height)
		return;
}

void init_textures(t_map_data *scrape)
{
	t_textures *tex_ptr;
	
	tex_ptr  = malloc(sizeof(t_textures) * 20);
	if (tex_ptr == NULL)
		return;
	scrape->tex = tex_ptr;
	load_texture(scrape, scrape->no, &scrape->tex[0]);
	load_texture(scrape, scrape->so, &scrape->tex[1]);
	load_texture(scrape, scrape->we, &scrape->tex[2]);
	load_texture(scrape, scrape->ea, &scrape->tex[3]);

	load_texture(scrape,"textures/door.xpm", &scrape->tex[4]);
	load_texture(scrape,"textures/wall_frame/1.xpm", &scrape->tex[5]);
	load_texture(scrape,"textures/wall_frame/2.xpm", &scrape->tex[6]);
	load_texture(scrape,"textures/wall_frame/3.xpm", &scrape->tex[7]);
	load_texture(scrape,"textures/wall_frame/4.xpm", &scrape->tex[8]);
	load_texture(scrape,"textures/wall_frame/5.xpm", &scrape->tex[9]);
	load_texture(scrape,"textures/wall_frame/6.xpm", &scrape->tex[10]);
	load_texture(scrape,"textures/wall_frame/7.xpm", &scrape->tex[11]);
}


void window_init(t_map_data *scrape)
{
    t_mlx_img *ptr;
	
	ptr = malloc(sizeof(t_mlx_img));
	if (!ptr)
		return ;
	scrape->img = ptr;
	ptr->mouse_x = 0;
    ptr->mouse_y = 0;
	ptr->mlx = mlx_init();
	ptr->mlx_win = mlx_new_window(ptr->mlx, WIDTH, HEIGHT, "cub3D");
	ptr->img = mlx_new_image(ptr->mlx, WIDTH, HEIGHT);
	ptr->addr = mlx_get_data_addr(ptr->img, &ptr->bits_per_pixel, &ptr->line_length, &ptr->endian);
	init_textures(scrape);
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
	window_init(scrape);
}