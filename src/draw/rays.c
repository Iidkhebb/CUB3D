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
    *step = (double)ptr->tex[ptr->tex_index].img_height / ptr->lineheight;
    if (ptr->lineheight < HEIGHT)
        ptr->tex_pos = 0;
    else 
        ptr->tex_pos = ((ptr->lineheight / 2) - (HEIGHT / 2)) * *step;
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
        if (y < ptr->drawstart)
            my_mlx_pixel_put(ptr, x, y, create_trgb(0, ptr->c[0],ptr->c[1],ptr->c[2]));
        else if (y >= ptr->drawstart && y <= ptr->drawend)
        {
            tex_y = (int)ptr->tex_pos % ptr->tex[ptr->tex_index].img_height;
            check_frames(ptr, &i, &frames);
            my_mlx_pixel_put(ptr, x, y, get_color(&ptr->tex[ptr->tex_index], tex_x, tex_y));
            ptr->tex_pos += step;
        }
        else
            my_mlx_pixel_put(ptr, x, y, create_trgb(0, ptr->f[0],ptr->f[1],ptr->f[2]));
    }
}


void validatd_DIR(t_map_data *ptr, int mapx,int mapy)
{
    if (ptr->raydirx < 0)
    {
        ptr->stepx = -1;
        ptr->sidedistx = (ptr->posx - mapx) * ptr->deltadistx;
    }
    else
    {
        ptr->stepx = 1;
        ptr->sidedistx = (mapx + 1.0 - ptr->posx) * ptr->deltadistx;
    }

    if (ptr->raydiry < 0)
    {
        ptr->stepy = -1;
        ptr->sidedisty = (ptr->posy - mapy) * ptr->deltadisty;
    }
    else
    {
        ptr->stepy = 1;
        ptr->sidedisty = (mapy + 1.0 - ptr->posy) * ptr->deltadisty;
    }
}

void ray_casting_extra(t_map_data *ptr, int mapx, int mapy)
{
    if(ptr->map[mapx][mapy] == 'D')
    {
        ptr->door_open = true;
        if (ptr->is_open == 1)
            open_door(ptr, mapx, mapy);
        ptr->save_door_x = mapx;
        ptr->save_door_y = mapy;
    }
    else if (ptr->is_open == 0)
    {
        ptr->map[ptr->save_door_x][ptr->save_door_y] = 'D';
    }
}

void ray_casting_extra_2(t_map_data *ptr, int *mapx, int *mapy, int x)
{
    ptr->camerax = (2 * x) / (double)WIDTH - 1;
    ptr->raydirx = ptr->dirx + ptr->planex * ptr->camerax;
    ptr->raydiry = ptr->dirY + ptr->planey * ptr->camerax;
    *mapx = (int)ptr->posx;
    *mapy = (int)ptr->posy;
    ptr->deltadistx = fabs(1 / ptr->raydirx);
    ptr->deltadisty = fabs(1 / ptr->raydiry);
}

void ray_casting(t_map_data *ptr)
{
    int x;
    int mapx;
    int mapy;
    int hit;
    int side;

    x = -1;
    side = 0;
    while (x++ < WIDTH)
    {
        ray_casting_extra_2(ptr, &mapx, &mapy, x);
        hit = 0;
        validatd_DIR(ptr, mapx,mapy);
        while (hit == 0)
        {
            ptr->door_open = false;
            check_wall_hit(ptr, &mapy, &mapx, &side);
            if (ptr->map[mapx][mapy] != '0') 
                hit = 1;
            ray_casting_extra(ptr, mapx, mapy);
        }
        set_draw_start_end(ptr, side);
        set_which_textures(ptr, side);
        draw_screen(ptr, side, x);
    }
}