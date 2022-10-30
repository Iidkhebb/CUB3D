#include "../../includes/cub3d.h"

unsigned int	get_color(t_textures *ptr, int x, int y)
{
	char	*color;
	int		pixel;

	pixel = (y * ptr->size_line) + (x * (ptr->bpp / 8));
	color = ptr->data + pixel;
	return (create_trgb(0, (unsigned char)color[2],
			(unsigned char)color[1], (unsigned char)color[0]));
}


void draw_screen(t_map_data *ptr, int side, int x) {
    double wallx;
    int tex_x;
    int tex_y;
    double step;
    double tex_pos;

    if (side == 0) {
        wallx = ptr->posY + (ptr->perpWallDist * ptr->rayDirY);
    } else {
        wallx = ptr->posX + (ptr->perpWallDist * ptr->rayDirX);
    }
    wallx -= (int)wallx;
    tex_x = wallx * ((double)ptr->tex[0].img_width);
    step = (double)ptr->tex[0].img_height / ptr->lineHeight;

    if (ptr->lineHeight < HEIGHT) {
        tex_pos = 0;
    } else {
        tex_pos = ((ptr->lineHeight/2) - (HEIGHT/2)) * step;
    }

    int y = 0;
    while (y < HEIGHT)
    {
        if (y < ptr->drawStart)
            my_mlx_pixel_put(ptr, x, y, create_trgb(0, ptr->C[0],ptr->C[1],ptr->C[2]) );

        else if (y >= ptr->drawStart && y <= ptr->drawEnd)
        {
            // if (side == 0)
                tex_y = (int)tex_pos % ptr->tex[0].img_height;
                my_mlx_pixel_put(ptr, x, y, get_color(&ptr->tex[0], tex_x, tex_y));
                tex_pos += step;
            // else
                // my_mlx_pixel_put(ptr, x, y, create_trgb(0, 68,141,13) * ((y > (HEIGHT / 2)) ? 3 : 0));
        }
        else
            my_mlx_pixel_put(ptr, x, y, create_trgb(0, ptr->F[0],ptr->F[1],ptr->F[2]));
        y++;
    }
}


void validatd_DIR(t_map_data *ptr, int mapX,int mapY)
{
    if (ptr->rayDirX < 0)
    {
        ptr->stepX = -1;
        ptr->sideDistX = (ptr->posX - mapX) * ptr->deltaDistX;
    }
    else
    {
        ptr->stepX = 1;
        ptr->sideDistX = (mapX + 1.0 - ptr->posX) * ptr->deltaDistX;
    }

    if (ptr->rayDirY < 0)
    {
        ptr->stepY = -1;
        ptr->sideDistY = (ptr->posY - mapY) * ptr->deltaDistY;
    }
    else
    {
        ptr->stepY = 1;
        ptr->sideDistY = (mapY + 1.0 - ptr->posY) * ptr->deltaDistY;
    }
}

void ray_casting(t_map_data *ptr)
{
    int x;
    int mapX;
    int mapY;
    int hit;
    int side;
    x = 0;
    mapX = 0;
    mapY = 0;
    side = 0;


    while (x < WIDTH)
    {
        ptr->cameraX = (2 * x) / (double)WIDTH - 1;
        ptr->rayDirX = ptr->dirX + ptr->planeX * ptr->cameraX;
        ptr->rayDirY = ptr->dirY + ptr->planeY * ptr->cameraX;
        
        mapX = (int)ptr->posX ;
        mapY = (int)ptr->posY ;

        ptr->deltaDistX = fabs(1 / ptr->rayDirX);
        ptr->deltaDistY = fabs(1 / ptr->rayDirY);
        hit = 0;

        validatd_DIR(ptr, mapX,mapY);

        while (hit == 0)
        {
            if (ptr->sideDistX < ptr->sideDistY)
            {
                ptr->sideDistX += ptr->deltaDistX;
                mapX += ptr->stepX;
                side = 0;
            }
            else
            {
                ptr->sideDistY += ptr->deltaDistY;
                mapY += ptr->stepY;
                side = 1;
            }
            if (ptr->map[mapX][mapY] != '0') hit = 1;
        }
        
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

        draw_screen(ptr, side, x);
        x++;
    }
    
}