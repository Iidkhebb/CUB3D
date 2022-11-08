#include "../../includes/cub3d.h"

void set_player_first_view(t_map_data *ptr)
{
    if (ptr->P_view == 'N')
    {
        ptr->dirX = -1;
        ptr->dirY = 0;
        ptr->planeX = 0;
        ptr->planeY = 0.66;
    }
    else if (ptr->P_view == 'S')
    {
        ptr->dirX = 1;
        ptr->dirY = 0;
        ptr->planeX = 0;
        ptr->planeY = -0.66;
    }
    else if (ptr->P_view == 'E')
    {
        ptr->dirX = 0;
        ptr->dirY = 1;
        ptr->planeX = 0.66;
        ptr->planeY = 0;
    }
    else if (ptr->P_view == 'W')
    {
        ptr->dirX = 0;
        ptr->dirY = -1;
        ptr->planeX = -0.66;
        ptr->planeY = 0;
    }
}

void init_player(t_map_data *ptr)
{
    set_player_first_view(ptr);
    ptr->posY = ptr->p_y;
    ptr->posX = ptr->p_x;
    ptr->is_open = 0;
    ptr->is_pressed_W = 0;
    ptr->is_pressed_S = 0;
    ptr->is_pressed_A = 0;
    ptr->is_pressed_D = 0;
    ptr->is_pressed_LEFT = 0;
    ptr->is_pressed_RIGHT = 0;
     ptr->save_door_x = 0;
    ptr->save_door_y = 0;

    
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
            if (ft_strchr(PLAYER_POS, ptr->map[i][j]))
            {
                ptr->p_x = i;
                ptr->p_y = j;
                ptr->p_x_mini = i;
                ptr->p_y_mini = j;
                ptr->P_view = ptr->map[i][j]; 
            }
            j++;
        }
        i++;
    }
    init_player(ptr);
}

