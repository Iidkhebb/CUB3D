#include "../../includes/cub3d.h"

char *check_open(char *path, char *line, t_map_data **scrape)
{
    int fd;
    char *new_path;

    new_path = ft_substr(path, 0, ft_strlen(path) - 1);
    fd = open(new_path, O_RDONLY);
    if (fd < 0)
    {
        free(line);
        ft_putstr_fd(ERR_TEXTURES_PATH, 2);
        close(fd);
        exit(FAILED);
    }
    // free(new_path);
    close(fd);
    return new_path ;
}

int get_textures_val(char *line, t_map_data **scrape, t_garbage **junk_list)
{
    t_map_data *s;

    if (!line)
        return 1;
    s = *scrape;
    if (!ft_strcmp( "NO ", garbage( junk_list, ft_substr(line, 0, 3))))
    {
        s->no = check_open(garbage(junk_list, ft_strtrim(&line[3], \
            WHITE_SPACES)), line, scrape);
    }
    else if (!ft_strcmp("SO ", garbage(junk_list, ft_substr(line, 0, 3))))
    {
        s->so = check_open(garbage(junk_list, ft_strtrim(&line[3], \
            WHITE_SPACES)), line, scrape);
    }
    else if (!ft_strcmp("WE ", garbage( junk_list, ft_substr(line, 0, 3))))
    {
        s->we = check_open(garbage(junk_list, ft_strtrim(&line[3], \
            WHITE_SPACES)), line, scrape);
    }
    else if (!ft_strcmp("EA ", garbage( junk_list, ft_substr(line, 0, 3))))
    {
        s->ea = check_open(garbage(junk_list, ft_strtrim(&line[3], \
            WHITE_SPACES)), line, scrape);
    }
    return (1);
}

int *process_RGB_data_extra(char **RGB)
{
    static int  out[3];

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


int *process_RGB_data(char *line, t_map_data **scrape)
{
    char **RGB;
    static int  out[3];
    int len;

    if (count_char(line, ',') != 2)
    {
        free(line);
        free(*scrape);
        ft_putstr_fd(ERR_RGB_VAL, 2);
        exit(FAILED);
    }
    RGB = ft_split(line, ',');
    len = (double_array_len(RGB));
    if (!RGB || !RGB[2] || !RGB[1] || !RGB[0] || len != 3)
    {
        free(line);
        free(*scrape);
        ft_putstr_fd(ERR_RGB_VAL, 2);
        exit(FAILED);
    }
    return process_RGB_data_extra(RGB);
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
        RGB = process_RGB_data(garbage(junk_list , \
            ft_strtrim( garbage(junk_list, ft_substr(&line[2], 0, \
                ft_strlen(&line[2]) - 1)), WHITE_SPACES)), scrape);
        s->c[0] = RGB[0];
        s->c[1] = RGB[1];
        s->c[2] = RGB[2];
    }
    else if (!ft_strcmp("F ", garbage(junk_list, ft_substr(line, 0, 2))))
    {
        RGB = process_RGB_data(garbage(junk_list , \
            ft_strtrim( garbage(junk_list, ft_substr(&line[2], 0, \
                ft_strlen(&line[2]) - 1)), WHITE_SPACES)), scrape);
        s->f[0] = RGB[0];
        s->f[1] = RGB[1];
        s->f[2] = RGB[2];
    }
    return 1;
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
        if (ft_strchr(WHITE_SPACES, line[i]))
            new_line[i] = '-';
        else
            new_line[i] = line[i];
        i++;
    }
    while (i < max_len)
        new_line[i++] = '-';
    new_line[i] = '\0';
    return (new_line);
}



char **convert_map(char **raw_map)
{
    char **map;
	int max;
    int i;

    if (!raw_map)
        return NULL;
    i = 0;
    max = get_greatest_line_len(raw_map);
    map = (char **)malloc(sizeof(char *) * ( tab_len(raw_map) + 1));
    while (raw_map[i])
    {
        map[i] = append_zero(raw_map[i], max);
        i++;
    }
    map[i] = NULL;
	return map;
}

t_map_data *scraper(int fd, char **raw_map)
{
    char        *line;
    t_garbage   *junk_list;
    t_map_data  *scrape;

    junk_list = NULL;
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
    }
    list_free(&junk_list);
    scrape->map = convert_map(raw_map);
    scrape->map_mini = convert_map(raw_map);
    return (scrape);
}