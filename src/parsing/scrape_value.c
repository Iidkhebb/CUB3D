#include "../../includes/cub3d.h"

int check_open(char *path, char *line, t_map_data **scrape)
{
    int fd;
    char *new_path;

    new_path = ft_substr(path, 0, ft_strlen(path) - 1);
    fd = open(new_path, O_RDONLY);
    if (fd < 0)
    {
        free(line);
        ft_putstr_fd(ERR_TEXTURES_PATH, 2);
        return (close(fd), exit(FAILED), 1);
    }
    free(new_path);
    return fd ;
}

int get_textures_val(char *line, t_map_data **scrape, t_garbage **junk_list)
{
    t_map_data *s;

    if (!line)
        return 1;

    s = *scrape;
    if (!ft_strcmp( "NO ", garbage( junk_list, ft_substr(line, 0, 3) ) ) )
        s->NO = check_open(garbage(junk_list, ft_strtrim(&line[3], WHITE_SPACES)), line, scrape);
    else if (!ft_strcmp("SO ", garbage( junk_list, ft_substr(line, 0, 3) ) ) )
        s->SO = check_open(garbage(junk_list, ft_strtrim(&line[3], WHITE_SPACES)), line, scrape);
    else if (!ft_strcmp("WE ", garbage( junk_list, ft_substr(line, 0, 3) ) ) )
        s->WE = check_open(garbage(junk_list, ft_strtrim(&line[3], WHITE_SPACES)), line, scrape);
    else if (!ft_strcmp("EA ", garbage( junk_list, ft_substr(line, 0, 3) ) ) )
        s->EA = check_open(garbage(junk_list, ft_strtrim(&line[3], WHITE_SPACES)), line, scrape);
    return 1;
}

int range(int n)
{
    if (n >= 0 && n <= 255)
        return 1;
    return 0;
}

int double_array_len(char **array)
{
    int i;

    i = 0;
    while (array[i])
        i++;
    return i;
}

int *process_RGB_data(char *line, t_map_data **scrape)
{
    char **RGB;
    static int  out[3];
    int len;

    RGB = ft_split(line, ',');
    len = (double_array_len(RGB));
    if (!RGB || !RGB[2] || !RGB[1] || !RGB[0] || len != 3)
    {
        free(line);
        free(*scrape);
        ft_putstr_fd(ERR_RGB_VAL, 2);
        exit(FAILED);
    }

    out[0] = ft_atoi(RGB[0]);
    out[1] = ft_atoi(RGB[1]);
    out[2] = ft_atoi(RGB[2]);

    free(RGB[0]);
    free(RGB[1]);
    free(RGB[2]);
    free(RGB);

    if (!(range(out[0]) && range(out[1]) && range(out[2])))
    {
        ft_putstr_fd(ERR_RGB_RNG, 2);
        exit(FAILED);
    }
    return out;
}

int get_RGB_val(char *line, t_map_data **scrape, t_garbage **junk_list)
{
    int *RGB;
    t_map_data *s;

    if (!line)
        return 1;
    s = *scrape;
    if (!ft_strcmp("C ", garbage(junk_list, ft_substr(line, 0, 2))))
    {
        RGB = process_RGB_data(garbage(junk_list , ft_strtrim( garbage(junk_list, ft_substr(&line[2], 0, ft_strlen(&line[2]) - 1)), WHITE_SPACES)), scrape);
        s->C[0] = RGB[0];
        s->C[1] = RGB[1];
        s->C[2] = RGB[2];
    }
    else if (!ft_strcmp("F ", garbage(junk_list, ft_substr(line, 0, 2))))
    {
        RGB = process_RGB_data(garbage(junk_list , ft_strtrim( garbage(junk_list, ft_substr(&line[2], 0, ft_strlen(&line[2]) - 1)), WHITE_SPACES)), scrape);
        s->F[0] = RGB[0];
        s->F[1] = RGB[1];
        s->F[2] = RGB[2];
    }
    return 1;
}

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

int get_greatest_line_len(t_maplines *list)
{
    int i;
    int len;
    int max;
    t_maplines *tmp;

    i = 0;
    len = 0;
    max = 0;
    tmp = list;
    while (tmp)
    {
        len = ft_strlen(tmp->line);
        if (len > max)
            max = len;
        tmp = tmp->next;
        i++;
    }
    return max;
}


char *append_zero(char *line, int max_len)
{
    int i;
    int len;
    char *new_line;

    if (!line)
        return NULL;
    i = 0;
    len = ft_strlen(line);
    new_line = (char *)malloc(sizeof(char) * (max_len));

    if (!new_line)
        return NULL;
    while (i < len && line[i] != '\n')
    {
        if (line[i] == ' ')
            new_line[i] = '0';
        else
            new_line[i] = line[i];
        i++;
    }
    while (i < max_len)
    {
        new_line[i] = '0';
        i++;
    }
    new_line[i] = '\0';
    return new_line;
}


char **convert_list_2_tab(t_maplines *list)
{
	t_maplines	*tmp;
	t_maplines	*lst;
    char **map;
	int i = 0;
    tmp = list;
    lst = list;
    map = malloc(sizeof(char *) * ft_lstsize(tmp));
    if (!map)
        return NULL;
    int max = get_greatest_line_len(lst);
	while (lst)
	{
		map[i] = append_zero(lst->line, max);
        lst = lst->next;
		i++;
	} 
	return map;
}

t_map_data *scraper(int fd)
{
    char        *line;
    t_garbage   *junk_list;
    t_map_data  *scrape;
    t_maplines  *map;


    junk_list = NULL;
    map = NULL;
    scrape = (t_map_data *)malloc(sizeof(t_map_data));
    if (!scrape)
        return 0;
    while (line)
    {
        line = get_next_line(fd);
        garbage(&junk_list, line);
        if ((line && check_empty_line(line, &junk_list)))
            continue;
        
        line = ft_strtrim(line, WHITE_SPACES);
        garbage(&junk_list, line);
        get_textures_val(line, &scrape, &junk_list);
        get_RGB_val(line, &scrape, &junk_list);
        get_MAP_val(&map, line);
    }
    list_free(&junk_list);
    scrape->data = map;
    scrape->map = convert_list_2_tab(map);
    return scrape;
}