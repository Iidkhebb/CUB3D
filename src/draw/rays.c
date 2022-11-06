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

void draw_screen(t_map_data *ptr, int side, int x) 
{
    int tex_x;
    int tex_y;
    double step;
    int y;
    
    y = -1;
    static int i = 5;
    static int frames = 0;
    tex_x = calc_tex_x(ptr, side);
    step = (double)ptr->tex[ptr->tex_index].img_height / ptr->lineHeight;
    if (ptr->lineHeight < HEIGHT)
        ptr->tex_pos = 0;
    else 
        ptr->tex_pos = ((ptr->lineHeight / 2) - (HEIGHT / 2)) * step;
    while (y++ < HEIGHT)
    {
        if (y < ptr->drawStart)
            my_mlx_pixel_put(ptr, x, y, create_trgb(0, ptr->C[0],ptr->C[1],ptr->C[2]));
        else if (y >= ptr->drawStart && y <= ptr->drawEnd)
        {
            tex_y = (int)ptr->tex_pos % ptr->tex[ptr->tex_index].img_height;
            if(ptr->tex_index == 5)
            {
                    frames++;
                    
                    ptr->tex_index = i;
                    
                    if (frames < 6000)
                    {
                        if (i == 10)
                            i = 5;
                
                    }
                    else
                    {
                        frames = 0;
                        i++;
                    }
                    
            }
            my_mlx_pixel_put(ptr, x, y, get_color(&ptr->tex[ptr->tex_index], tex_x, tex_y));
            ptr->tex_pos += step;
        }
        else
            my_mlx_pixel_put(ptr, x, y, create_trgb(0, ptr->F[0],ptr->F[1],ptr->F[2]));
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


void ray_casting(t_map_data *ptr)
{
    int x;
    int mapX;
    int mapY;
    int hit;
    int side;

    x = -1;
    side = 0;
    while (x++ < WIDTH)
    {
        ptr->cameraX = (2 * x) / (double)WIDTH - 1;
        ptr->rayDirX = ptr->dirX + ptr->planeX * ptr->cameraX;
        ptr->rayDirY = ptr->dirY + ptr->planeY * ptr->cameraX;
        mapX = (int)ptr->posX;
        mapY = (int)ptr->posY;
        ptr->deltaDistX = fabs(1 / ptr->rayDirX);
        ptr->deltaDistY = fabs(1 / ptr->rayDirY);
        hit = 0;
        validatd_DIR(ptr, mapX,mapY);
        while (hit == 0)
        {
            ptr->door_open = false;
            check_wall_hit(ptr, &mapY, &mapX, &side);
            if (ptr->map[mapX][mapY] != '0') hit = 1;
            
            if(ptr->map[mapX][mapY] == 'D')
            {
                ptr->door_open = true;
                if (ptr->is_open == 1)
                    open_door(ptr, mapX, mapY);
                ptr->save_door_x = mapX;
                ptr->save_door_y = mapY;
            }
            else if (ptr->is_open == 0)
            {
                ptr->map[ptr->save_door_x][ptr->save_door_y] = 'D';
            }

        }
        set_draw_start_end(ptr, side);
        set_which_textures(ptr, side);
        draw_screen(ptr, side, x);
    }
}