#ifndef cub3d_H
# define cub3d_H

#include <libc.h>
#include <mlx.h>
# include "../LIBFT/libft.h"
# include "../GNL/get_next_line.h"
#include <math.h>
# include<stdbool.h>

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
#define VALID_CHAR "10 DNSEW"

#define SIZE 8
#define BOX_SIZE 30
#define WIDTH 1280
#define HEIGHT 720

#define SPEED 0.1
# define ESPACE 49
# define W 13
# define S 1
# define A 0
# define D 2
# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define EXIT 69

# define ROTATION_SPEED 0.1

// STRUCTS
typedef struct s_map_data
{
    char *NO;
    char *SO;
    char *WE;
    char *EA;

    int C[3];
    int F[3];

    char **map;
    char **map_MINI;
    // structs
    struct s_maplines *data;
    struct s_mlx_img *img;
    struct s_textures *tex;
    struct s_mlx_img *door; // <<
    bool door_open; // <<

    
    // Player
    int length_line;
    float p_angle;
    float *dists;
    double p_x;
    double p_y;
    int p_x_mini;
    int p_y_mini;
    char P_view;
    // Ray
    double posX;
    double posY;

    double dirX;
    double dirY;

    double planeX;
    double planeY;

    double cameraX;
    double rayDirX;
    double rayDirY;

    int mapX;
    int mapY;

    double deltaDistX;
    double deltaDistY;
    double sideDistX;
    double sideDistY;
    double perpWallDist;
    int stepX;
    int stepY;
    int lineHeight;
    int drawStart;
    int drawEnd;
    int is_pressed_W;
    int is_pressed_S;
    int is_pressed_A;
    int is_pressed_D;

    int is_pressed_LEFT;
    int is_pressed_RIGHT;

    // textures

    double tex_pos;
    int tex_index;

    int is_open;
    int save_door_x;
    int save_door_y;
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

typedef struct s_vector {
	double	x;
	double	y;
}				t_vector;

typedef struct s_maplines
{
    char *line;
    struct s_maplines *next;
} t_maplines;

typedef struct s_textures
{
    int     img_width;
    int		img_height;
    void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
} t_textures;

typedef struct s_garbage
{
    char *garbage_lines;
    
    struct s_garbage *next;
} t_garbage;

// PROTOTYPES
int basic_init(int ac, char *av[]);
char **check_map(int fd);
int check_empty_line(char *line, t_garbage **junk);
t_map_data *scraper(int fd, char **raw_map);


char *garbage(t_garbage **junk, char *line);
t_garbage	*ft_lstnew(char *junk);
t_garbage	*ft_lstlast(t_garbage *lst);
void	ft_lstadd_back(t_garbage **lst, t_garbage *new);
void	list_free(t_garbage **list);
int	ft_lstsize(t_maplines *lst);

void ray_casting(t_map_data *ptr);
void	my_mlx_pixel_put(t_map_data *data, int x, int y, int color);
int tab_len(char **tab);
t_maplines	*ft_lstnew_map(char *line);
t_maplines	*ft_lstlast_map(t_maplines *lst);
void	ft_lstadd_back_map(t_maplines **lst, t_maplines *new);
void	list_free_map(t_map_data **list);
void mini_map(t_map_data *ptr);
int	create_trgb(int t, int r, int g, int b);
int get_greatest_line_len(char **raw_map);
void mlx_warper(t_map_data *scrape);
void get_player_pos(t_map_data *ptr);
void get_player_pos(t_map_data *ptr);
void change_player_pos(t_map_data *ptr, int keycode);

void open_door(t_map_data *ptr, int x, int y);
void close_door(t_map_data *ptr, int x, int y);

int valid_texture(char *line);
int valid_map(char *line);
int check_player_pos(char *line, int *is_player);
int tab_len(char **tab);
char *trim_whitescapes(char *line);
char **list_to_tab(t_maplines *list);
int free_tab(char **tab);
void free_list(t_maplines *list);
#endif