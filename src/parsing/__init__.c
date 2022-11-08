#include "../../includes/cub3d.h"


// char check_map_extra()
// {}

char **check_map(int fd)
{
    t_garbage		*junk_list;
    char *line;
    int map_level;
    static char *prv;
    int is_done;
    t_maplines *maplines;
    char *trim;
    char **tab;
    maplines = NULL;
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
        trim = ft_strtrim(line, WHITE_SPACES);
        garbage(&junk_list, trim);
        map_level = valid_texture(trim);
        if (!map_level)
            return (ft_putstr_fd(ERR_TEXTURES_KEY, 2), list_free(&junk_list), exit(1) ,NULL);
        else if ((prv && check_empty_line(line, &junk_list)) || (prv && !line))
        {
            is_done = 1;
        }
        else if ((map_level == 454 || map_level == -1))
        {
            if (is_done && !check_empty_line(line, &junk_list))
                return (ft_putstr_fd(ERR_MAPS_ENDLINE, 2),list_free(&junk_list), free_list(maplines),exit(1), NULL);

            if (line)
                ft_lstadd_back_map(&maplines, ft_lstnew_map(line));
            prv = line;
        }
    }

    tab = list_to_tab(maplines);
    if (!check_walls(tab))
        return (ft_putstr_fd(ERR_MAPS_WALL, 2), list_free(&junk_list), free_tab(tab) ,exit(1), NULL);

    list_free(&junk_list);
    free_list(maplines);
    return tab;
}