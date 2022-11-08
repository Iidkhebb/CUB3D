#include "../../includes/cub3d.h"



void final_check( t_maplines *maplines, char **tab, t_garbage *junk_list)
{
    if (!check_walls(tab))
        return (ft_putstr_fd(ERR_MAPS_WALL, 2), list_free(&junk_list), free_tab(tab) ,exit(1));

    list_free(&junk_list);
    free_list(maplines);
    return ;
}

int check_endline(int is_done, char *line, t_garbage **junk_list, t_maplines **maplines)
{
    if (is_done && !check_empty_line(line, junk_list))
        return (ft_putstr_fd(ERR_MAPS_ENDLINE, 2),list_free(junk_list), free_list(*maplines),exit(1), 0);
    if (line)
        ft_lstadd_back_map(maplines, ft_lstnew_map(line));
    return (1);
}

void iter_line(char *line, t_garbage **junk_list, int *map_level)
{
    char *trim;

    trim = ft_strtrim(line, WHITE_SPACES);
    garbage(junk_list, trim);
    *map_level = valid_texture(trim);
}
void check_text_key(t_garbage **junk_list, int map_level)
{
    if (!map_level)
        return (ft_putstr_fd(ERR_TEXTURES_KEY, 2), list_free(junk_list), exit(1));
}

void iter_extra(char *line,  t_garbage **junk_list, int *map_level, int is_done)
{
    garbage(junk_list, line);
    if ((line && check_empty_line(line, junk_list) \
        && (*map_level != 454)) \
            || (is_done && check_empty_line(line, junk_list)))
    {
        return ;
    }
    iter_line(line, junk_list, map_level);
    check_text_key(junk_list, *map_level);
    return ;
}

char **init_tab(t_maplines **maplines, t_garbage **junk_list)
{
    char **tab;
    tab = list_to_tab(*maplines);
    final_check(*maplines, tab, *junk_list);
    return (tab);
}

char **check_map(int fd)
{
    t_garbage		*junk_list;
    char *line;
    int map_level;
    static char *prv;
    int is_done;
    t_maplines *maplines;

    maplines = NULL;
    is_done = 0;
    map_level = 0;
    prv = NULL;
    junk_list = NULL;
    while(line)
    {
        line = get_next_line(fd);
        iter_extra(line, &junk_list, &map_level, is_done);
        if ((prv && check_empty_line(line, &junk_list)) || (prv && !line))
            is_done = 1;
        else if ((map_level == 454 || map_level == -1))
        {
            check_endline(is_done, line, &junk_list, &maplines);
            prv = line;
        }
    }
    return init_tab(&maplines, &junk_list);
}