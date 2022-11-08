#include "../../includes/cub3d.h"

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
    line = "";
    while(line)
    {
        line = get_next_line(fd);
        iter_extra(line, &junk_list, &map_level, is_done);
        if ((prv && check_empty_line(line)) || (prv && !line))
            is_done = 1;
        else if ((map_level == 454 || map_level == -1))
        {
            check_endline(is_done, line, &junk_list, &maplines);
            prv = line;
        }
    }
    return init_tab(&maplines, &junk_list);
}