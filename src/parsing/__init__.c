#include "../../includes/cub3d.h"
int just_free(char *line)
{
    return 1;
}

int basic_init(int ac, char *av[])
{
    int fd;

    if (ac != 2)
        return (ft_putstr_fd(ERR_ARGS, 2), exit(FAILED), 1);
    fd = open(av[1], O_RDONLY);
    if (fd < 0 || ft_strcmp(&av[1][ft_strlen(av[1]) - 4], ".cub"))
        return (ft_putstr_fd(ERR_PATH, 2), exit(FAILED), 1);
    return fd;
}

int valid_texture(char *line)
{
    int i;
    static int  total;
    
    i = 0;
    if (!line)
        return -1;
    if (ft_strchr(TEXTURES_KEYS, line[i]) && ft_strchr(AFTER_KEY, line[i + 1]) && line[i + 2] == ' ') 
        return (total += (int)line[i], 1);
    if (ft_strchr(RGB_KEY, line[i]) && line[i + 1] == ' ')
        return (total += (int)line[i], 1);
    if (total != 454)
        return (0);
    return 454;
}

int valid_map(char *line)
{
    int i;
    
    i = 0;

    if (!line)
        return 1;

    while (line[i] != '\n' && line[i] != '\0')
    {
        if (!ft_strchr(VALID_CHAR, line[i]))
            return 0;
        else 
            i++;
    }
    return 1;
}

int check_player_pos(char *line, int *is_player)
{
    int i;
    if (!line)
        return 1;
    i = 0;
    while (line[i] && line[i] !='\0')
    {
        if (ft_strchr(PLAYER_POS, line[i]) && (line[i + 1] == '1' || line[i + 1] == '0'))
        {
            *is_player += 1;
            return  1;
        }
        i++;
    }
    return 0;
}

int check_walls(char *l_prv, char *l_curr)
{
    int i;

    i = 0;
    if (l_curr)
    {
        if ((l_curr[0] != '1') || (l_curr[ft_strlen(l_curr) - 2]) != '1')
            return 0;
        while (l_curr[i] != '\0')
        {
            if (!l_prv && l_curr[i] == '0') // check first line
                return 0;
            if (l_prv && l_curr[i] == ' ') // check last line from space
                if (i <= ft_strlen(l_prv) && l_prv[i] == '0' )
                    return 0;
            if (l_prv && l_prv[i] == ' ') // check first line from space
                if (i <= ft_strlen(l_curr) && l_curr[i] == '0' )
                    return 0;
            i++;
        }
    }
    return 1;
}

char *garbage(t_garbage **junk, char *line)
{
    if (!line)
        return NULL;
    ft_lstadd_back(junk, ft_lstnew(line));
    return line;
}


int check_map(int fd)
{
    t_garbage		*junk_list;
    char *line;
    int map_level;
    static char *prv;
    int is_done;
    static int player = 0;
    
    is_done = 0;
    map_level = 0;
    prv = NULL;
    junk_list = NULL;
    while(line)
    {
        line = get_next_line(fd);
        garbage(&junk_list, line);
        if ((line && check_empty_line(line, &junk_list) && (map_level != 454)) || (is_done && check_empty_line(line, &junk_list)))
            continue;
        line = ft_strtrim(line, WHITE_SPACES);
        garbage(&junk_list, line);
        map_level = valid_texture(line);
        if (!map_level)
            return (ft_putstr_fd(ERR_TEXTURES_KEY, 2), list_free(&junk_list), 1);
        else if ((prv && check_empty_line(line, &junk_list)) || (prv && !line))
        {
            if (ft_strchr(prv, '0'))
                return (ft_putstr_fd(ERR_MAPS_WALL, 2),list_free(&junk_list), 1);
            is_done = 1;
        }
        else if ((map_level == 454 || map_level == -1))
        {
            if (is_done && !check_empty_line(line, &junk_list))
                return (ft_putstr_fd(ERR_MAPS_ENDLINE, 2),list_free(&junk_list), 1);
            check_player_pos(line, &player);
            if (!valid_map(line))
                return (ft_putstr_fd(ERR_MAPS_VAL, 2), list_free(&junk_list), 1);

            if (!check_walls(prv, line))
                return (ft_putstr_fd(ERR_MAPS_WALL, 2), list_free(&junk_list), 1);
            
            prv = line;
        }
    }
   
    if (player != 1)
        return (ft_putstr_fd(ERR_MAPS_PLAYER, 2), list_free(&junk_list), 1);

    list_free(&junk_list);
    return 0;
}