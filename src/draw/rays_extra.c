#include "../../includes/cub3d.h"

void set_which_textures(t_map_data *ptr, int side)
{
    if (side == 0 )
    {
        if (ptr->rayDirX > 0)
            ptr->tex_index = 5;
        else    
            ptr->tex_index = 0;
    }
    else 
    {
        if (ptr->rayDirY > 0)
            ptr->tex_index = 3;
        else
            ptr->tex_index = 2;
    }
    if(ptr->door_open)
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

int  calc_tex_x(t_map_data *ptr, int side)
{
    double wallx;

    if (side == 0) {
        wallx = ptr->posY + (ptr->perpWallDist * ptr->rayDirY);
    } else {
        wallx = ptr->posX + (ptr->perpWallDist * ptr->rayDirX);
    }
    wallx -= (int)wallx;
    return(wallx * ((double)ptr->tex[ptr->tex_index].img_width));
}

void set_draw_start_end(t_map_data *ptr, int side)
{
    if (side == 0)
        ptr->perpWallDist = (ptr->sideDistX - ptr->deltaDistX);
    else
        ptr->perpWallDist = (ptr->sideDistY - ptr->deltaDistY);
    ptr->lineHeight = (int)(HEIGHT / ptr->perpWallDist);
    ptr->drawStart = (-ptr->lineHeight / 2) + (HEIGHT / 2);
    if (ptr->drawStart < 0)
        ptr->drawStart = 0;
    ptr->drawEnd = (ptr->lineHeight / 2) + (HEIGHT / 2);
    if (ptr->drawEnd >= HEIGHT)
        ptr->drawEnd = HEIGHT - 1;
}

void check_wall_hit(t_map_data *ptr, int *mapY,int *mapX, int *side)
{
    if (ptr->sideDistX < ptr->sideDistY)
    {
        ptr->sideDistX += ptr->deltaDistX;
        *mapX += ptr->stepX;
        *side = 0;
    }
    else
    {
        ptr->sideDistY += ptr->deltaDistY;
        *mapY += ptr->stepY;
        *side = 1;
    }
}
