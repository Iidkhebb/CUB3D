#include "../../includes/cub3d.h"


void mini_map(t_map_data *ptr)
{
	int i = 0;
	int j = 0;
	int SIZE = 8;
	
	while (ptr->map_MINI[i])
	{
		j = 0;
		while (ptr->map_MINI[i][j])
		{
			
			if (ptr->map_MINI[i][j] == '0')
			{
				int x1 = 0;
				int y1 = 0;
				while (++x1 < SIZE)
				{
					y1 = -1;
					while (++y1 < SIZE)
					{
						my_mlx_pixel_put(ptr, j * SIZE + x1, i  * SIZE + y1 -1 , create_trgb(100, 172, 229, 219));
					}
				}
				
			}
			else if (ptr->map_MINI[i][j] == '1')
			{
				int x1 = 0;
				int y1 = 0;
				while (++x1 < SIZE)
				{
					y1 = -1;
					while (++y1 < SIZE)
					{
						my_mlx_pixel_put(ptr, j * SIZE + x1, i  * SIZE + y1 -1, create_trgb(0, 50, 20, 0));
					}
				}
				
			}
			else if (ptr->map_MINI[i][j] == 'N' || ptr->map_MINI[i][j] == 'S' || ptr->map_MINI[i][j] == 'E' || ptr->map_MINI[i][j] == 'W')
			{
				int x1 = 0;
				int y1 = 0;
				while (++x1 < 10)
				{
					y1 = -1;
					while (++y1 < 10)
					{
						my_mlx_pixel_put(ptr, ptr->posY * SIZE + x1, ptr->posX  * SIZE + y1, create_trgb(0, 255, 0, 0));
					}
				}
			}
			j++;
		}
		i++;
	}
}