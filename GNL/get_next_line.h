#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#define BUFFER_SIZE 1024

/* INCLUDES */
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
/* PROTOTYPES */
char	*get_next_line(int fd);
char	*ft_add_char(char *big, char *c);

#endif