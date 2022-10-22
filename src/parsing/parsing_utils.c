#include "../../includes/cub3d.h"

int check_empty_line(char *line)
{
    int i;
	char *check;

    i = 0;
    if (ft_strlen(line) == 0 || line[0] == '\n')
		return 1;
    check = ft_strtrim(line, WHITE_SPACES);
	if (check[0] == '\n')
		return (free(check), 1);
	return (0);
}