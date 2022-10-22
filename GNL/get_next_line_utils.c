#include "get_next_line.h"

char	*ft_add_char(char *str, char *c)
{
	int		len;
	char	*n;
	int		i;

	i = -1;
	len = 0;
	while (str[len++]){}
	n = (char *) malloc(len + 2);
	if (n == NULL)
		return (free(str), NULL);
	while (str[++i])
		n[i] = str[i];
	n[i++] = *c;
	n[i] = 0;
	return (free(str), n);
}