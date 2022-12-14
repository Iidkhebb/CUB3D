/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidkhebb <iidkhebb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:58:42 by iidkhebb          #+#    #+#             */
/*   Updated: 2022/11/08 22:25:17 by iidkhebb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_something(t_map_data *ptr, double i, double j, int color)
{
	int	x1;
	int	y1;

	x1 = 0;
	y1 = 0;
	while (++x1 < SIZE)
	{
		y1 = -1;
		while (++y1 < SIZE)
			mmpp(ptr, j * SIZE + x1, i * SIZE + y1, color);
	}
}

void	mini_map(t_map_data *ptr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ptr->map_mini[i])
	{
		j = 0;
		while (ptr->map_mini[i][j])
		{
			if (ft_strchr(PLAYER_POS, ptr->map_mini[i][j]) \
				|| ptr->map_mini[i][j] == '0')
				draw_something(ptr, i, j, create_trgb(0, 100, 255, 255));
			else if (ptr->map_mini[i][j] == '1')
				draw_something(ptr, i, j, create_trgb(0, 7, 9, 9));
			else if (ptr->map_mini[i][j] == 'D')
				draw_something(ptr, i, j, create_trgb(0, 255, 255, 255));
			j++;
		}
		i++;
	}
	draw_something(ptr, ptr->posx, ptr->posy, create_trgb(0, 255, 0, 0));
}

void	ray_casting_extra_two(t_map_data *ptr, int *mapx, int *mapy, int x)
{
	ptr->camerax = (2 * x) / (double)WIDTH - 1;
	ptr->raydirx = ptr->dirx + ptr->planex * ptr->camerax;
	ptr->raydiry = ptr->diry + ptr->planey * ptr->camerax;
	*mapx = (int)ptr->posx;
	*mapy = (int)ptr->posy;
	ptr->deltadistx = fabs(1 / ptr->raydirx);
	ptr->deltadisty = fabs(1 / ptr->raydiry);
}

void	ray_casting(t_map_data *ptr)
{
	int	x;
	int	mapx;
	int	mapy;
	int	hit;
	int	side;

	x = -1;
	side = 0;
	while (x++ < WIDTH)
	{
		ray_casting_extra_two(ptr, &mapx, &mapy, x);
		hit = 0;
		validatd_dir(ptr, mapx, mapy);
		while (hit == 0)
		{
			ptr->door_open = false;
			check_wall_hit(ptr, &mapy, &mapx, &side);
			if (ptr->map[mapx][mapy] != '0')
				hit = 1;
			ray_casting_extra(ptr, mapx, mapy);
		}
		set_draw_start_end(ptr, side);
		set_which_textures(ptr, side);
		draw_screen(ptr, side, x);
	}
}
