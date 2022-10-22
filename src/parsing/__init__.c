#include "../../includes/cub3d.h"

int just_free(char *line)
{
    return (free(line), 1);
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
    while (line[i] != '\n' && line[i] != '\0')
    {
        if (!ft_strchr(VALID_CHAR, line[i]))
            return 0;
        else 
            i++;
    }
    return 1;
}

int check_walls(char *l_prv, char *l_curr)
{
    int i;

    i = 0;
    if (!l_curr && ft_strchr(l_prv, '0'))
        return 0;
    else if (l_curr)
    {
        if (l_curr[0] != '1' || l_curr[ft_strlen(l_curr) - 2] != '1')
                return 0;
        while (l_curr[i] != '\0')
        {
            if (!l_prv && l_curr[i] == '0')
                return 0;
            if (l_prv && l_curr[i] == ' ')
            {
                if (i <= ft_strlen(l_prv) && l_prv[i] == '0' )
                    return 0;
            }
            else if (l_prv && l_prv[i] == ' ')
                if (i <= ft_strlen(l_curr) && l_curr[i] == '0' )
                    return 0;
            i++;
        }
    }
    return 1;
}

int check_map(int fd)
{
    char *line;
    int map_level = 0;
    char *prv;

    prv = NULL;
    while(line)
    {
        line = get_next_line(fd);
        if (line && check_empty_line(line) && just_free(line) && (map_level != 454))
            continue;
        line = ft_strtrim(line, WHITE_SPACES);
        map_level = valid_texture(line);
        if (!map_level)
            return (ft_putstr_fd(ERR_TEXTURES_KEY, 2), 1);
        else if (map_level == 454 || map_level == -1)
        {
            if (line && !valid_map(line))
                return (ft_putstr_fd(ERR_MAPS_VAL, 2), 1);
            if (!check_walls(prv, line))
                return (ft_putstr_fd(ERR_MAPS_WALL, 2), 1);
            free(prv);
            prv = ft_strdup(line);
        }
        printf("%s", line);
        free(line);
    }
    free(prv);
    return 0;
}