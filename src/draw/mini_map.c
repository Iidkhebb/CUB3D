#include "../../includes/cub3d.h"


void mini_map(t_map_data *ptr)
{
	int i = 0;
	int j = 0;
	int SIZE = 26;
	
	while (ptr->map[i])
	{
		j = 0;
		while (ptr->map[i][j])
		{
			
			if (ptr->map[i][j] == '0')
			{
				int x1 = 0;
				int y1 = 0;
				while (++x1 < SIZE)
				{
					y1 = -1;
					while (++y1 < SIZE)
					{
						mlx_pixel_put(ptr->img->mlx, ptr->img->mlx_win, j * SIZE + x1, i  * SIZE + y1, create_trgb(0, 0, 0, 255));
					}
				}
				
			}
			else if (ptr->map[i][j] == 'N' || ptr->map[i][j] == 'S' || ptr->map[i][j] == 'E' || ptr->map[i][j] == 'W')
			{
				int x1 = 0;
				int y1 = 0;
				while (++x1 < SIZE)
				{
					y1 = -1;
					while (++y1 < SIZE)
					{
						mlx_pixel_put(ptr->img->mlx, ptr->img->mlx_win, j * SIZE + x1, i  * SIZE + y1, create_trgb(0, 255, 0, 0));
					}
				}
			}
			else if (ptr->map[i][j] == '1')
			{
				int x1 = 0;
				int y1 = 0;
				while (++x1 < SIZE)
				{
					y1 = -1;
					while (++y1 < SIZE)
					{
						mlx_pixel_put(ptr->img->mlx, ptr->img->mlx_win, j * SIZE + x1, i  * SIZE + y1, create_trgb(150, 50, 20, 0));
					}
				}
				
			}
			j++;
		}
		i++;
	}
}