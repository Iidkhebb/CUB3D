#include "../../includes/cub3d.h"

void init_player(t_map_data *ptr)
{
    ptr->posY = ptr->p_y;
    ptr->posX = ptr->p_x;
    ptr->dirX = -1;
    ptr->dirY = 0;
    ptr->planeX = 0;
    ptr->planeY = 0.66;
    ptr->is_pressed_W = 0;
    ptr->is_pressed_S = 0;
    ptr->is_pressed_A = 0;
    ptr->is_pressed_D = 0;
    ptr->is_pressed_LEFT = 0;
    ptr->is_pressed_RIGHT = 0;
    
}

void get_player_pos(t_map_data *ptr)
{
    int i;
    int j;

    i = 0;
    while (ptr->map[i])
    {
        j = 0;
        while (ptr->map[i][j])
        {
            if (ptr->map[i][j] == 'N' || ptr->map[i][j] == 'S' || ptr->map[i][j] == 'E' || ptr->map[i][j] == 'W')
            {
                ptr->p_x = i;
                ptr->p_y = j;
            }
            j++;
        }
        i++;
    }
    init_player(ptr);
}

void change_player_pos(t_map_data *ptr, int keycode)
{
    if (keycode == W)
    {
        if (ptr->map[ptr->p_x - 1][ptr->p_y] == '0')
        {
            ptr->map[ptr->p_x][ptr->p_y] = '0';
            ptr->map[ptr->p_x - 1][ptr->p_y] = 'N';
            // ptr->p_x--;
        }

    }
    else if (keycode == S)
    {
        if (ptr->map[ptr->p_x + 1][ptr->p_y] == '0')
        {
            ptr->map[ptr->p_x][ptr->p_y] = '0';
            ptr->map[ptr->p_x + 1][ptr->p_y] = 'N';
            // ptr->p_x++;
        }
    }
    else if (keycode == A)
    {
        if (ptr->map[ptr->p_x][ptr->p_y - 1] == '0')
        {
            ptr->map[ptr->p_x][ptr->p_y] = '0';
            ptr->map[ptr->p_x][ptr->p_y - 1] = 'N';
            // ptr->p_y--;
        }
    }
    else if (keycode == D)
    {
        if (ptr->map[ptr->p_x][ptr->p_y + 1] == '0')
        {
            ptr->map[ptr->p_x][ptr->p_y] = '0';
            ptr->map[ptr->p_x][ptr->p_y + 1] = 'N';
            // ptr->p_y++;
        }
    }
}