#include "../../includes/cub3d.h"

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
        }
    
        i++;
    }
    return 0;
}

int tab_len(char **tab)
{
    int i;
    i = 0;
    while (tab[i])
        i++;
    return i;
}


char *trim_whitescapes(char *line)
{
    int i;
    int j;
    char *tmp;
    char *new_line;

    i = 0;
    j = 0;
    tmp = ft_strdup(line);
    new_line = ft_calloc(ft_strlen(tmp) + 1, sizeof(char));
    while (tmp[i] != '\n')
    {
        if (!ft_strchr(WHITE_SPACES, tmp[i]))
        {
            new_line[j] = tmp[i];
            j++;
        }
        i++;
    }
    free(tmp);
    return new_line;
}