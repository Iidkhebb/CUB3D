#include "../../includes/cub3d.h"

int check_open(char *path, char *line, t_map_data *scrape)
{
    int fd;

    fd = open(ft_substr(path, 0, ft_strlen(path) - 1), O_RDONLY);
    printf("%s | fd:%d\n", path, fd);
    if (fd < 0)
    {
        free(line);
        free(scrape);
        ft_putstr_fd(ERR_TEXTURES_PATH, 2);
        return (close(fd), exit(FAILED), 1);
    }
    return fd ;
}

int get_textures_val(char *line, t_map_data *scrape)
{
    if (!line)
        return 1;
    
    if (!ft_strcmp("NO ", ft_substr(line, 0, 3)))
        scrape->NO = check_open(ft_strtrim(&line[3], WHITE_SPACES), line, scrape);
    else if (!ft_strcmp("SO ", ft_substr(line, 0, 3)))
        scrape->SO = check_open(ft_strtrim(&line[3], WHITE_SPACES), line, scrape);
    else if (!ft_strcmp("WE ", ft_substr(line, 0, 3)))
        scrape->WE = check_open(ft_strtrim(&line[3], WHITE_SPACES), line, scrape);
    else if (!ft_strcmp("EA ", ft_substr(line, 0, 3)))
        scrape->EA = check_open(ft_strtrim(&line[3], WHITE_SPACES), line, scrape);
    
    return 1;
}

int *process_RGB_data(char *line, t_map_data *scrape)
{
    char **RGB;
    static int  out[3];

    RGB = ft_split(line, ',');
    if (!RGB || !RGB[2] || !RGB[1] || !RGB[0])
    {
        free(line);
        free(scrape);
        ft_putstr_fd(ERR_RGB_VAL, 2);
        exit(FAILED);
    }

    out[0] = ft_atoi(RGB[0]);
    out[1] = ft_atoi(RGB[1]);
    out[2] = ft_atoi(RGB[2]);
    return out;
}

int get_RGB_val(char *line, t_map_data *scrape)
{
    int *RGB;

    if (!line)
        return 1;

    if (!ft_strcmp("C ", ft_substr(line, 0, 2)))
    {
        RGB = process_RGB_data(ft_strtrim(ft_substr(&line[2], 0, ft_strlen(&line[2]) - 1), WHITE_SPACES), scrape);
        scrape->C[0] = RGB[0];
        scrape->C[1] = RGB[1];
        scrape->C[2] = RGB[2];
    }
    else if (!ft_strcmp("F ", ft_substr(line, 0, 2)))
    {
        RGB = process_RGB_data(ft_strtrim(ft_substr(&line[2], 0, ft_strlen(&line[2]) - 1), WHITE_SPACES), scrape);
        scrape->F[0] = RGB[0];
        scrape->F[1] = RGB[1];
        scrape->F[2] = RGB[2];
    }
    return 1;
}

int scraper(t_map_data *scrape, int fd)
{
    char *line;

    scrape = malloc(sizeof(t_map_data *));
    if (!scrape)
        return 0;
    while (line)
    {
        line = get_next_line(fd);
        if ((line && check_empty_line(line) && just_free(line)))
            continue;
        
        line = ft_strtrim(line, WHITE_SPACES);
        get_textures_val(line, scrape);
        get_RGB_val(line, scrape);
        
        free(line);
    }
    printf("%d,%d,%d\n", scrape->C[0], scrape->C[1], scrape->C[2]);
    printf("%d,%d,%d\n", scrape->F[0], scrape->F[1], scrape->F[2]);
    return 1;
}