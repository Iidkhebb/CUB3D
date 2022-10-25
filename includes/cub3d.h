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
#define ERR_RGB_RNG "Error : Invalid RGB OUT OF RANGE\n"
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

#define WIDTH 1280
#define HEIGHT 720

// STRUCTS
typedef struct s_map_data
{
    int NO;
    int SO;
    int WE;
    int EA;

    int C[3];
    int F[3];
    struct s_maplines *data;
    struct s_mlx_img *img;
    
} t_map_data;

typedef struct s_mlx_img
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;

    void	*mlx;
	void	*mlx_win;

    // KEYBOARD
    int key_press;
    int key_release;
    // MOUSE
    int mouse_x;
    int mouse_y;
    int mouse_hook;
} t_mlx_img;

typedef struct s_maplines
{
    char *line;
    struct s_maplines *next;
} t_maplines;



typedef struct s_garbage
{
    char *garbage_lines;
    
    struct s_garbage *next;
} t_garbage;

// PROTOTYPES
int basic_init(int ac, char *av[]);
int check_map(int fd);
int check_empty_line(char *line, t_garbage **junk);
t_map_data *scraper(int fd);
int just_free(char *line);


char *garbage(t_garbage **junk, char *line);
t_garbage	*ft_lstnew(char *junk);
t_garbage	*ft_lstlast(t_garbage *lst);
void	ft_lstadd_back(t_garbage **lst, t_garbage *new);
void	list_free(t_garbage **list);

t_maplines	*ft_lstnew_map(char *line);
t_maplines	*ft_lstlast_map(t_maplines *lst);
void	ft_lstadd_back_map(t_maplines **lst, t_maplines *new);
void	list_free_map(t_map_data **list);


void mlx_warper(t_map_data *scrape);
#endif