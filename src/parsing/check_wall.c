#include "../../includes/cub3d.h"

int deep_check_walls_one(char **tab, int i, int j)
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
        if (!deep_check_walls_one(tab, i, j))
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