#include "../../includes/cub3d.h"

int deepcheck_extra(char **tab, int i, int j)
{
    if((tab[i][j] == '0' && tab[i + 1][j] == ' ') || (tab[i][j] == '0' && tab[i - 1][j] == ' '))
        return (0);
    if (ft_strlen(tab[i]) > ft_strlen(tab[i - 1]))
    {
        if (tab[i][j] == '0' && j > ft_strlen(tab[i - 1]))
            return (0);
    }
    else if (ft_strlen(tab[i]) > ft_strlen(tab[i + 1]))
    {
        if (tab[i][j] == '0' && j > ft_strlen(tab[i + 1]))
            return (0);
    }
    return (1);
}


int deep_check_walls_1(char **tab, int i, int j)
{
    if (deepcheck_extra(tab, i, j) == 0)
        return (0);
    if (ft_strchr("D", tab[i][j]) && (tab[i][j + 1] != '1' || tab[i][j - 1] != '1') \
         && (tab[i + 1][j] != '1' || tab[i - 1][j] != '1'))
    {
        return (0);
    }
    else if (ft_strchr("D", tab[i][j]) && (tab[i + 1][j] != '1' || tab[i - 1][j] != '1') \
        && (tab[i][j + 1] != '1' || tab[i][j - 1] != '1'))
    {
        return (0);
    }
    if (tab[i][j] == '0' && (tab[i][j + 1] == ' ' || tab[i][j - 1] == ' '))
        return (0);
    if (ft_strchr(PLAYER_POS, tab[i][j]) && (tab[i][j + 1] == '1' && tab[i][j - 1] == '1') \
        && (tab[i + 1][j] == '1' && tab[i - 1][j] == '1'))
    {
        return (ft_putstr_fd("Error: PLayer invalid position\n", 2), 0);
    }
    return (1);
}

int check_first_line(char **tab)
{
    int j;

    j = 0;
    while (tab[0][j] != '\n')
    {
        if (!ft_strchr(WHITE_SPACES, tab[0][j]) && tab[0][j] != '1')
            return  (0);
        j++;
    }
    return (1);
}

int check_last_line(char **tab, int last)
{
    int j;

    j = 0;
    while (tab[last][j]  != '\n' && tab[last][j] != '\0') // last one has no '\n'
    {
        if (!ft_strchr(" 1", tab[last][j]) && tab[last][j] != '1')
            return (0);
        j++;
    }
    return (1);
}
int check_inner_walls(char **tab, int i)
{
    char *trim;
    int j;

    j = 0;
    trim = trim_whitescapes(tab[i]);
    if (trim[0] != '1' || trim[ft_strlen(trim) - 1] != '1') // checking if first and last char are '1'
        return (0);
    free(trim); 
    while (tab[i][j] != '\0' && tab[i][j] != '\n')
    {
        if (!deep_check_walls_1(tab, i, j))
            return (0);
        j++;
    }
    return (1);
}

int check_walls(char **tab)
{
    int i;
    int j;
    int p_count;
    char *trim;
    int last;

    i = 0;
    p_count = 0;
    last = tab_len(tab) - 1;
    while (tab[i])
    {
        j = 0;
        check_player_pos(tab[i], &p_count);
        if (!valid_map(tab[i]))
            return (0);
        if (!check_first_line(tab)) // checking first line to have only '1' or ' '
            return (0);
        else if (i == last && !check_last_line(tab, last)) // checking last line to have only '1' or ' '
            return (0);
        else if (i != 0 && i != last && !check_inner_walls(tab, i)) // checking inside
            return (0);
        i++;
    }
    if (p_count != 1)
        return (ft_putstr_fd(ERR_MAPS_PLAYER, 2), 0);
    return 1;
}


char **check_map(int fd)
{
    t_garbage		*junk_list;
    char *line;
    int map_level;
    static char *prv;
    int is_done;
    static int player = 0;
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

    // checking walls
    tab = list_to_tab(maplines);
    if (!check_walls(tab))
        return (ft_putstr_fd(ERR_MAPS_WALL, 2), list_free(&junk_list), free_tab(tab) ,exit(1), NULL);

    list_free(&junk_list);
    free_list(maplines);
    return tab;
}