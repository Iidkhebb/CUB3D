/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidkhebb <iidkhebb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:56:34 by iidkhebb          #+#    #+#             */
/*   Updated: 2022/11/08 22:25:17 by iidkhebb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_which_textures(t_map_data *ptr, int side)
{
	if (side == 0)
	{
		if (ptr->raydirx > 0)
			ptr->tex_index = 5;
		else
			ptr->tex_index = 0;
	}
	else
	{
		if (ptr->raydiry > 0)
			ptr->tex_index = 3;
		else
			ptr->tex_index = 2;
	}
	if (ptr->door_open)
		ptr->tex_index = 4;
}

unsigned int	get_color(t_textures *ptr, int x, int y)
{
	char	*color;
	int		pixel;

	pixel = (y * ptr->size_line) + (x * (ptr->bpp / 8));
	color = ptr->data + pixel;
	return (create_trgb(0, (unsigned char)color[2],
			(unsigned char)color[1], (unsigned char)color[0]));
}

int	calc_tex_x(t_map_data *ptr, int side)
{
	double	wallx;

	if (side == 0)
	{
		wallx = ptr->posy + (ptr->perpwalldist * ptr->raydiry);
	}
	else
	{
		wallx = ptr->posx + (ptr->perpwalldist * ptr->raydirx);
	}
	wallx -= (int)wallx;
	return (wallx * ((double)ptr->tex[ptr->tex_index].img_width));
}

void	set_draw_start_end(t_map_data *ptr, int side)
{
	if (side == 0)
		ptr->perpwalldist = (ptr->sidedistx - ptr->deltadistx);
	else
		ptr->perpwalldist = (ptr->sidedisty - ptr->deltadisty);
	ptr->lineheight = (int)(HEIGHT / ptr->perpwalldist);
	ptr->drawstart = (-ptr->lineheight / 2) + (HEIGHT / 2);
	if (ptr->drawstart < 0)
		ptr->drawstart = 0;
	ptr->drawend = (ptr->lineheight / 2) + (HEIGHT / 2);
	if (ptr->drawend >= HEIGHT)
		ptr->drawend = HEIGHT - 1;
}

void	check_wall_hit(t_map_data *ptr, int *mapy, int *mapx, int *side)
{
	if (ptr->sidedistx < ptr->sidedisty)
	{
		ptr->sidedistx += ptr->deltadistx;
		*mapx += ptr->stepx;
		*side = 0;
	}
	else
	{
		ptr->sidedisty += ptr->deltadisty;
		*mapy += ptr->stepy;
		*side = 1;
	}
}
