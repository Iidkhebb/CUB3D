#include "../../includes/cub3d.h"

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

int range(int n)
{
    if (n >= 0 && n <= 255)
        return 1;
    return 0;
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

char *check_open(char *path, char *line)
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
    close(fd);
    return new_path ;
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