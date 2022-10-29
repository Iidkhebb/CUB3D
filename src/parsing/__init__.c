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

int check_walls(char **tab)
{
    int i;
    int j;
    int p_count;
    char *trim;

    i = 0;
    p_count = 0;
    int last = tab_len(tab) - 1;
    while (tab[i])
    {
        j = 0;
        check_player_pos(tab[i], &p_count);
        if (!valid_map(tab[i]))
            return (0);
        

        if (i == 0) // checking first line to have only '1' or ' '
        {
            j = 0;
            while (tab[0][j] != '\n')
            {
                if (!ft_strchr(WHITE_SPACES, tab[0][j]) && tab[0][j] != '1')
                    return  (0);
                j++;
            }
        }
        else if (i == last) // checking last line to have only '1' or ' '
        {
            j = 0;
            while (tab[last][j]  != '\n' && tab[last][j] != '\0') // last one has no '\n'
            {
                if (!ft_strchr(" 1", tab[last][j]) && tab[last][j] != '1')
                    return (0);
                j++;
            }
        }
        else if (i != 0 && i != last) // checking inside
        {
            j = 0;
            trim = trim_whitescapes(tab[i]);
            if (trim[0] != '1' || trim[ft_strlen(trim) - 1] != '1') // checking if first and last char are '1'
                return (0);
            free(trim); 
            
            while (tab[i][j] != '\0' && tab[i][j] != '\n')
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
                j++;
            }

        }
        i++;
    }
    if (p_count != 1)
        return (ft_putstr_fd(ERR_MAPS_PLAYER, 2), 0);
    return 1;
}

char *garbage(t_garbage **junk, char *line)
{
    if (!line)
        return NULL;
    ft_lstadd_back(junk, ft_lstnew(line));
    return line;
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