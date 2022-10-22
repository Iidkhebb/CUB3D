#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			r[1];
	static char		*str;
	int				status;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (0);
	str = (char *)malloc(2 * sizeof(char));
	status = read(fd, r, 1);
	if (!str || status < 0)
		return (free(str), NULL);
	str[0] = *r;
	str[1] = '\0';
	while (status && str)
	{
		if (*r == '\n')
			return (str);
		status = read(fd, r, 1);
		if (status == 0)
			return (str);
		str = ft_add_char(str, r);
	}
	return (free(str), NULL);
}