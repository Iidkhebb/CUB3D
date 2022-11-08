/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidkhebb <iidkhebb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:21:39 by iidkhebb          #+#    #+#             */
/*   Updated: 2022/11/08 22:45:30 by iidkhebb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libc.h>
# include <mlx.h>
# include "../LIBFT/libft.h"
# include "../GNL/get_next_line.h"
# include <math.h>
# include<stdbool.h>

// DEFINES

# define ERR_ARGS "Error : Wrong count of agruments\n"
# define ERR_PATH "Error : Invalid Map Path\n"
# define ERR_TEXTURES_KEY "Error : Invalid Textures keys\n"
# define ERR_MAPS_VAL "Error : Invalid MAP Char\n"
# define ERR_MAPS_WALL "Error : Invalid MAP WALLS\n"
# define ERR_MAPS_PLAYER "Error : Invalid Player\n"
# define ERR_MAPS_ENDLINE "Error : Invalid MAPS endline\n"
# define ERR_TEXTURES_PATH "Error : Invalid Textures Path\n"
# define ERR_RGB_VAL "Error : Invalid RGB Values\n"
# define ERR_RGB_RNG "Error : Invalid RGB OUT OF RANGE\n"
# define FAILED  1
# define SUCCESS  0
# define WHITE_SPACES " \t\r\f\v"
# define TEXTURES_KEYS "NSWE"
# define AFTER_KEY "OEA"
# define RGB_KEY "FC"
# define WALL 1
# define FIELD 0
# define PLAYER_POS "NSEW"
# define VALID_CHAR "10 DNSEW"

# define SIZE 8
# define BOX_SIZE 30
# define WIDTH 1280
# define HEIGHT 720

# define SPEED 0.1
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
	char				*no;
	char				*so;
	char				*we;
	char				*ea;

	int					c[3];
	int					f[3];

	char				**map;
	char				**map_mini;
	struct s_maplines	*data;
	struct s_mlx_img	*img;
	struct s_textures	*tex;
	struct s_mlx_img	*door;
	bool				door_open;

	int					length_line;
	float				p_angle;
	float				*dists;
	double				p_x;
	double				p_y;
	int					p_x_mini;
	int					p_y_mini;
	char				p_view;
	double				posx;
	double				posy;
	double				dirx;
	double				diry;
	double				planex;
	double				planey;				
	double				camerax;
	double				raydirx;
	double				raydiry;

	int					mapx;
	int					mapy;

	double				deltadistx;
	double				deltadisty;
	double				sidedistx;
	double				sidedisty;
	double				perpwalldist;
	int					stepx;
	int					stepy;
	int					lineheight;
	int					drawstart;
	int					drawend;
	int					is_pressed_w;
	int					is_pressed_s;
	int					is_pressed_a;
	int					is_pressed_d;					
	int					is_pressed_left;
	int					is_pressed_right;

	double				tex_pos;
	int					tex_index;

	int					is_open;
	int					save_door_x;
	int					save_door_y;
}	t_map_data;

typedef struct s_mlx_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	void	*mlx;
	void	*mlx_win;
	int		key_press;
	int		key_release;
	int		mouse_x;
	int		mouse_y;
	int		mouse_hook;
}	t_mlx_img;

typedef struct s_vector {
	double	x;
	double	y;
}				t_vector;

typedef struct s_maplines
{
	char				*line;
	struct s_maplines	*next;
}	t_maplines;

typedef struct s_textures
{
	int		img_width;
	int		img_height;
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_textures;

typedef struct s_garbage
{
	char				*garbage_lines;
	struct s_garbage	*next;
}	t_garbage;

// PROTOTYPES
int				basic_init(int ac, char *av[]);
int				check_empty_line(char *line);
t_map_data		*scraper(int fd, char **raw_map);

char			*garbage(t_garbage **junk, char *line);
t_garbage		*ft_lstnew(char *junk);
t_garbage		*ft_lstlast(t_garbage *lst);
void			ft_lstadd_back(t_garbage **lst, t_garbage *new);
void			list_free(t_garbage **list);
int				ft_lstsize(t_maplines *lst);
void			ray_casting(t_map_data *ptr);
void			mmpp(t_map_data *data, int x, int y, int color);
int				tab_len(char **tab);
t_maplines		*ft_lstnew_map(char *line);
t_maplines		*ft_lstlast_map(t_maplines *lst);
void			ft_lstadd_back_map(t_maplines **lst, t_maplines *new);
void			list_free_map(t_map_data **list);
void			mini_map(t_map_data *ptr);
int				create_trgb(int t, int r, int g, int b);
int				get_greatest_line_len(char **raw_map);
void			mlx_warper(t_map_data *scrape);
void			get_player_pos(t_map_data *ptr);
void			get_player_pos(t_map_data *ptr);
void			change_player_pos(t_map_data *ptr, int keycode);

void			open_door(t_map_data *ptr, int x, int y);
void			close_door(t_map_data *ptr, int x, int y);	
int				valid_texture(char *line);
int				valid_map(char *line);
int				check_player_pos(char *line, int *is_player);
int				tab_len(char **tab);
char			*trim_whitescapes(char *line);
char			**list_to_tab(t_maplines *list);
int				free_tab(char **tab);
void			free_list(t_maplines *list);
char			*check_open(char *path, char *line);
int				range(int n);
int				double_array_len(char **array);
int				count_char(char *line, char c);
int				get_map_val(t_maplines **scrape, char *line);
int				ft_lstsize(t_maplines *lst);
int				get_greatest_line_len(char **raw_map);
int				check_walls(char **tab);
int				calc_tex_x(t_map_data *ptr, int side);
unsigned int	get_color(t_textures *ptr, int x, int y);
void			set_which_textures(t_map_data *ptr, int side);
void			set_draw_start_end(t_map_data *ptr, int side);
void			check_wall_hit(t_map_data *ptr, int *mapY, \
				int *mapX, int *side);
void			_d_mouvements(t_map_data *ptr);
void			_d_mouvemenst_sides(t_map_data *ptr);
void			mmpp(t_map_data *data, int x, int y, int color);
int				key_release(int keycode, t_map_data *ptr);
int				key_press(int keycode, t_map_data *ptr);
int				mouse_move_hook(int x, int y, t_map_data *ptr);
int				close_window(t_map_data *ptr);
void			ray_casting_extra_two(t_map_data *ptr, int *mapx, \
				int *mapy, int x);
void			ray_casting(t_map_data *ptr);
void			draw_screen(t_map_data *ptr, int side, int x);
void			ray_casting_extra(t_map_data *ptr, int mapx, int mapy);
void			validatd_dir(t_map_data *ptr, int mapx, int mapy);
char			**init_tab(t_maplines **maplines, t_garbage **junk_list);
char			**check_map(int fd, t_maplines **maplines);
int				check_endline(int is_done, char *line, \
				t_garbage **junk_list, t_maplines **maplines);
void			iter_extra(char *line, t_garbage **junk_list, \
				int *map_level, int is_done);
void			final_check( t_maplines *maplines, \
				char **tab, t_garbage *junk_list);
int				deepcheck_extra(char **tab, int i, int j);
int				valid_texture(char *line);
char			*append_zero(char *line, int max_len);
char			**convert_map(char **raw_map);
void			get_text_val_extra(char *line, t_map_data **s, \
				t_garbage **junk_list);
#endif