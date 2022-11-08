#include "../../includes/cub3d.h"

int get_MAP_val(t_maplines **scrape, char *line)
{

    if (line &&  ((line[0] != '1') || (line[ft_strlen(line) - 2]) != '1'))
    {
        return 1;
    }
    else
    {
        ft_lstadd_back_map(scrape, ft_lstnew_map(line));
    }
    return 1;
}

int	ft_lstsize(t_maplines *lst)
{
	int	i;

	i = 0;
	while (lst)
    {
        lst = lst->next;
        i++;
    }
	return (i);
}

int get_greatest_line_len(char **raw_map)
{
    int i;
    int len;
    int max;
    
    i = 0;
    max = 0;
    while (raw_map[i])
    {
        len = ft_strlen(raw_map[i]);
        if (len > max)
            max = len;
        i++;
    }
    return max;
}



int double_array_len(char **array)
{
    int i;

    i = 0;
    while (array[i])
        i++;
    return i;
}

int count_char(char *line, char c)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (line[i])
    {
        if (line[i] == c)
            count++;
        i++;
    }
    return count;
}