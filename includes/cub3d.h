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
#define ERR_MAPS_WALL "Error : Invalid MAP WALLS\n"
#define ERR_MAPS_PLAYER "Error : Invalid Player\n"
#define ERR_MAPS_ENDLINE "Error : Invalid MAPS endline\n"
#define ERR_TEXTURES_PATH "Error : Invalid Textures Path\n"
#define ERR_RGB_VAL "Error : Invalid RGB Values\n"
#define FAILED  1
#define SUCCESS  0
# define WHITE_SPACES " \t\r\f\v"
#define TEXTURES_KEYS "NSWE"
#define AFTER_KEY "OEA"
#define RGB_KEY "FC"
#define WALL 1
#define FIELD 0
#define PLAYER_POS "NSEW"
#define VALID_CHAR "10 NSEW"

// DEFINES


typedef struct map_data
{
    int NO;
    int SO;
    int WE;
    int EA;

    int C[3];
    int F[3];

    char **map_lines;
} t_map_data;


int basic_init(int ac, char *av[]);
int check_map(int fd);
int check_empty_line(char *line);
int scraper(t_map_data *scrape, int fd);
int just_free(char *line);
#endif