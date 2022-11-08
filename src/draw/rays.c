/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidkhebb <iidkhebb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:53:05 by iidkhebb          #+#    #+#             */
/*   Updated: 2022/11/08 22:05:19 by iidkhebb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_frames(t_map_data *ptr, int *i, int *frames)
{
	if (ptr->tex_index == 5)
	{
		*frames = *frames + 1;
		ptr->tex_index = *i;
		if (*frames < 6000)
		{
			if (*i == 10)
				*i = 5;
		}
		else
		{
			*frames = 0;
			*i = *i + 1;
		}
	}
}

void	check_screen_h(t_map_data *ptr, double *step)
{
	*step = (double)ptr->tex[ptr->tex_index].img_height / ptr->lineheight;
	if (ptr->lineheight < HEIGHT)
		ptr->tex_pos = 0;
	else
		ptr->tex_pos = ((ptr->lineheight / 2) - (HEIGHT / 2)) * *step;
}

void	draw_screen(t_map_data *ptr, int side, int x)
{
	int			tex_x;
	int			tex_y;
	double		step;
	int			y;
	static int	frames = 0;
	static int	i = 5;
	
	y = -1;
	tex_x = calc_tex_x(ptr, side);
	check_screen_h(ptr, &step);
	while (y++ < HEIGHT)
	{
		if (y < ptr->drawstart)
			mmpp(ptr, x, y, create_trgb(0, ptr->c[0], ptr->c[1], ptr->c[2]));
		else if (y >= ptr->drawstart && y <= ptr->drawend)
		{
			tex_y = (int)ptr->tex_pos % ptr->tex[ptr->tex_index].img_height;
			check_frames(ptr, &i, &frames);
			mmpp(ptr, x, y, get_color(&ptr->tex[ptr->tex_index], tex_x, tex_y));
			ptr->tex_pos += step;
		}
		else
			mmpp(ptr, x, y, create_trgb(0, ptr->f[0], ptr->f[1], ptr->f[2]));
	}
}

void	validatd_dir(t_map_data *ptr, int mapx, int mapy)
{
	if (ptr->raydirx < 0)
	{
		ptr->stepx = -1;
		ptr->sidedistx = (ptr->posx - mapx) * ptr->deltadistx;
	}
	else
	{
		ptr->stepx = 1;
		ptr->sidedistx = (mapx + 1.0 - ptr->posx) * ptr->deltadistx;
	}
	if (ptr->raydiry < 0)
	{
		ptr->stepy = -1;
		ptr->sidedisty = (ptr->posy - mapy) * ptr->deltadisty;
	}
	else
	{
		ptr->stepy = 1;
		ptr->sidedisty = (mapy + 1.0 - ptr->posy) * ptr->deltadisty;
	}
}

void	ray_casting_extra(t_map_data *ptr, int mapx, int mapy)
{
	if (ptr->map[mapx][mapy] == 'D')
	{
		ptr->door_open = true;
		if (ptr->is_open == 1)
			open_door(ptr, mapx, mapy);
		ptr->save_door_x = mapx;
		ptr->save_door_y = mapy;
	}
	else if (ptr->is_open == 0)
	{
		ptr->map[ptr->save_door_x][ptr->save_door_y] = 'D';
	}
}
