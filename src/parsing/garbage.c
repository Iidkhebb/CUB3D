#include "../../includes/cub3d.h"

char *garbage(t_garbage **junk, char *line)
{
    if (!line)
        return NULL;
    ft_lstadd_back(junk, ft_lstnew(line));
    return line;
}

int deepcheck_extra(char **tab, int i, int j)
{
    if((tab[i][j] == '0' && tab[i + 1][j] == ' ') || (tab[i][j] == '0' && tab[i - 1][j] == ' '))
        return (0);
    if ((int)ft_strlen(tab[i]) > (int)ft_strlen(tab[i - 1]))
    {
        if (tab[i][j] == '0' && j > (int)ft_strlen(tab[i - 1]))
            return (0);
    }
    else if ((int)ft_strlen(tab[i]) > (int)ft_strlen(tab[i + 1]))
    {
        if (tab[i][j] == '0' && j > (int)ft_strlen(tab[i + 1]))
            return (0);
    }
    return (1);
}

char **list_to_tab(t_maplines *list)
{
    char **tab;
    int i;
    int size;

    i = 0;
    size = ft_lstsize(list);
    tab = (char **)malloc(sizeof(char *) * (size + 1));
    while (list)
    {
        tab[i] = list->line;
        list = list->next;
        i++;
    }
    tab[i] = NULL;
    return tab;
}

int free_tab(char **tab)
{
    int i;
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
    return 0;
}

void free_list(t_maplines *list)
{
    t_maplines *tmp;
    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}