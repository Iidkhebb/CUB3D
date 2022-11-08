#include "../../includes/cub3d.h"

void check_frames(t_map_data *ptr, int *i, int *frames)
{
    if(ptr->tex_index == 5)
    {
        *frames = *frames + 1;
        ptr->tex_index = *i;
        if (*frames < 6000)
        {
            if (*i == 10)
                *i = 5;
        }
        else
        {
            *frames = 0;
            *i = *i + 1;
        }  
    }
}

void check_screen_H(t_map_data *ptr, double *step)
{
    *step = (double)ptr->tex[ptr->tex_index].img_height / ptr->lineHeight;
    if (ptr->lineHeight < HEIGHT)
        ptr->tex_pos = 0;
    else 
        ptr->tex_pos = ((ptr->lineHeight / 2) - (HEIGHT / 2)) * *step;
}

void draw_screen(t_map_data *ptr, int side, int x) 
{
    int tex_x;
    int tex_y;
    double step;
    int y;
    static int frames = 0;
    static int i = 5;
    
    y = -1;
    tex_x = calc_tex_x(ptr, side);
    check_screen_H(ptr, &step);
    while (y++ < HEIGHT)
    {
        if (y < ptr->drawStart)
            my_mlx_pixel_put(ptr, x, y, create_trgb(0, ptr->C[0],ptr->C[1],ptr->C[2]));
        else if (y >= ptr->drawStart && y <= ptr->drawEnd)
        {
            tex_y = (int)ptr->tex_pos % ptr->tex[ptr->tex_index].img_height;
            check_frames(ptr, &i, &frames);
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

void ray_casting_extra(t_map_data *ptr, int mapX, int mapY)
{
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

void ray_casting_extra_2(t_map_data *ptr, int *mapX, int *mapY, int x)
{
    ptr->cameraX = (2 * x) / (double)WIDTH - 1;
    ptr->rayDirX = ptr->dirX + ptr->planeX * ptr->cameraX;
    ptr->rayDirY = ptr->dirY + ptr->planeY * ptr->cameraX;
    *mapX = (int)ptr->posX;
    *mapY = (int)ptr->posY;
    ptr->deltaDistX = fabs(1 / ptr->rayDirX);
    ptr->deltaDistY = fabs(1 / ptr->rayDirY);
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
        ray_casting_extra_2(ptr, &mapX, &mapY, x);
        hit = 0;
        validatd_DIR(ptr, mapX,mapY);
        while (hit == 0)
        {
            ptr->door_open = false;
            check_wall_hit(ptr, &mapY, &mapX, &side);
            if (ptr->map[mapX][mapY] != '0') 
                hit = 1;
            ray_casting_extra(ptr, mapX, mapY);
        }
        set_draw_start_end(ptr, side);
        set_which_textures(ptr, side);
        draw_screen(ptr, side, x);
    }
}