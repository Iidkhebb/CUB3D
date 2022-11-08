/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidkhebb <iidkhebb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:57:52 by iidkhebb          #+#    #+#             */
/*   Updated: 2022/11/08 22:25:17 by iidkhebb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_player_first_view(t_map_data *ptr)
{
	if (ptr->p_view == 'N')
	{
		ptr->dirx = -1;
		ptr->diry = 0;
		ptr->planex = 0;
		ptr->planey = 0.66;
	}
	else if (ptr->p_view == 'S')
	{
		ptr->dirx = 1;
		ptr->diry = 0;
		ptr->planex = 0;
		ptr->planey = -0.66;
	}
	else if (ptr->p_view == 'E')
	{
		ptr->dirx = 0;
		ptr->diry = 1;
		ptr->planex = 0.66;
		ptr->planey = 0;
	}
	else if (ptr->p_view == 'W')
	{
		ptr->dirx = 0;
		ptr->diry = -1;
		ptr->planex = -0.66;
		ptr->planey = 0;
	}
}

void	init_player(t_map_data *ptr)
{
	set_player_first_view(ptr);
	ptr->posy = ptr->p_y;
	ptr->posx = ptr->p_x;
	ptr->is_open = 0;
	ptr->is_pressed_w = 0;
	ptr->is_pressed_s = 0;
	ptr->is_pressed_a = 0;
	ptr->is_pressed_d = 0;
	ptr->is_pressed_left = 0;
	ptr->is_pressed_right = 0;
	ptr->save_door_x = 0;
	ptr->save_door_y = 0;
}

void	get_player_pos(t_map_data *ptr)
{
	int	i;
	int	j;

	i = 0;
	while (ptr->map[i])
	{
		j = 0;
		while (ptr->map[i][j])
		{
			if (ft_strchr(PLAYER_POS, ptr->map[i][j]))
			{
				ptr->p_x = i;
				ptr->p_y = j;
				ptr->p_x_mini = i;
				ptr->p_y_mini = j;
				ptr->p_view = ptr->map[i][j];
			}
			j++;
		}
		i++;
	}
	init_player(ptr);
}
