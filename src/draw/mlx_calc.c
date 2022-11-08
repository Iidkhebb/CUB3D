/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidkhebb <iidkhebb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:53:15 by iidkhebb          #+#    #+#             */
/*   Updated: 2022/11/08 22:25:17 by iidkhebb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_window(t_map_data *ptr)
{
	list_free_map(&ptr);
	exit(0);
	return (0);
}

void	open_door(t_map_data *ptr, int x, int y)
{
	if (ptr->map[x][y] == 'D')
	{
		ptr->map[x][y] = '0';
	}
}

void	close_door(t_map_data *ptr, int x, int y)
{
	if (ptr->map[x][y] == '0')
	{
		ptr->map[x][y] = 'D';
	}
}

int	mouse_move_hook(int x, int y, t_map_data *ptr)
{
	if (x < ptr->img->mouse_x && (x <= WIDTH && x >= 0))
	{
		ptr->dirx = ptr->dirx * cos(0.02) - ptr->diry * sin(0.02);
		ptr->diry = ptr->dirx * sin(0.02) + ptr->diry * cos(0.02);
		ptr->planex = ptr->planex * cos(0.02) - ptr->planey * sin(0.02);
		ptr->planey = ptr->planex * sin(0.02) + ptr->planey * cos(0.02);
	}
	else if (x > ptr->img->mouse_x && (x <= WIDTH && x >= 0))
	{
		ptr->dirx = ptr->dirx * cos(-0.02) - ptr->diry * sin(-0.02);
		ptr->diry = ptr->dirx * sin(-0.02) + ptr->diry * cos(-0.02);
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
