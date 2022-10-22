#ifndef cub3d_H
# define cub3d_H

#include <libc.h>
#include <mlx.h>
# include "../LIBFT/libft.h"
# include "../GNL/get_next_line.h"

// DEFINES

#define ERR_ARGS "Error : Wrong count of agruments\n"
#define ERR_PATH "Error : Invalid Map Path\n"
#define ERR_TEXTURES_KEY "Error : Invalid Textures keys\n"
#define ERR_MAPS_VAL "Error : Invalid MAP Char\n"
#define FAILED  1
#define SUCCESS  1
# define WHITE_SPACES " \t\r\f\v"
#define TEXTURES_KEYS "NSWE"
#define AFTER_KEY "OEA"
#define RGB_KEY "FC"
#define WALL 1
#define FIELD 0
#define PLAYER_POS "NSEW"
#define VALID_CHAR "10 NSEW"

// DEFINES


// typedef struct maps
// {

// }


int basic_init(int ac, char *av[]);
int check_map(int fd);
int check_empty_line(char *line);
#endif