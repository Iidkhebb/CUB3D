#include "../../includes/cub3d.h"

void draw_something(t_map_data *ptr, double i, double j, int color)
{
	int x1;
	int y1;

	x1 = 0;
	y1 = 0;
	while (++x1 < SIZE)
	{
		y1 = -1;
		while (++y1 < SIZE)
			my_mlx_pixel_put(ptr, j * SIZE + x1, i  * SIZE + y1 , color);
	}
}

void mini_map(t_map_data *ptr)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (ptr->map_mini[i])
	{
		j = 0;
		while (ptr->map_mini[i][j])
		{
			if (ft_strchr(PLAYER_POS, ptr->map_mini[i][j]) || ptr->map_mini[i][j] == '0')
				draw_something(ptr, i, j,create_trgb(0, 100, 255, 255));
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