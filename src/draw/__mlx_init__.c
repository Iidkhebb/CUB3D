/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __mlx_init__.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidkhebb <iidkhebb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:03:06 by iidkhebb          #+#    #+#             */
/*   Updated: 2022/11/08 22:04:56 by iidkhebb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	render_next_frame(t_map_data *ptr)
{
	_d_mouvements(ptr);
	ray_casting(ptr);
	mini_map(ptr);
	mlx_put_image_to_window(ptr->img->mlx, ptr->img->mlx_win, \
		ptr->img->img, 0, 0);
	return (1);
}

void	load_texture(t_map_data *ptr, char *filename, t_textures *t)
{
	t->img = mlx_xpm_file_to_image(ptr->img->mlx, filename, \
		&t->img_width, &t->img_height);
	if (!t->img || !filename)
		return ;
	t->data = mlx_get_data_addr(t->img, &t->bpp, &t->size_line, &t->endian);
	if (! t->data || t->img_width != t->img_height)
		return ;
}

void	init_textures(t_map_data *scrape)
{
	t_textures	*tex_ptr;

	tex_ptr = malloc(sizeof(t_textures) * 20);
	if (tex_ptr == NULL)
		return ;
	scrape->tex = tex_ptr;
	load_texture(scrape, scrape->no, &scrape->tex[0]);
	load_texture(scrape, scrape->so, &scrape->tex[1]);
	load_texture(scrape, scrape->we, &scrape->tex[2]);
	load_texture(scrape, scrape->ea, &scrape->tex[3]);
	load_texture(scrape, "textures/door.xpm", &scrape->tex[4]);
	load_texture(scrape, "textures/wall_frame/1.xpm", &scrape->tex[5]);
	load_texture(scrape, "textures/wall_frame/2.xpm", &scrape->tex[6]);
	load_texture(scrape, "textures/wall_frame/3.xpm", &scrape->tex[7]);
	load_texture(scrape, "textures/wall_frame/4.xpm", &scrape->tex[8]);
	load_texture(scrape, "textures/wall_frame/5.xpm", &scrape->tex[9]);
	load_texture(scrape, "textures/wall_frame/6.xpm", &scrape->tex[10]);
	load_texture(scrape, "textures/wall_frame/7.xpm", &scrape->tex[11]);
}

void	window_init(t_map_data *scrape)
{
	t_mlx_img	*ptr;

	ptr = malloc(sizeof(t_mlx_img));
	if (!ptr)
		return ;
	scrape->img = ptr;
	ptr->mouse_x = 0;
	ptr->mouse_y = 0;
	ptr->mlx = mlx_init();
	ptr->mlx_win = mlx_new_window(ptr->mlx, WIDTH, HEIGHT, "cub3D");
	ptr->img = mlx_new_image(ptr->mlx, WIDTH, HEIGHT);
	ptr->addr = mlx_get_data_addr(ptr->img, &ptr->bits_per_pixel, \
		&ptr->line_length, &ptr->endian);
	init_textures(scrape);
	mlx_hook(ptr->mlx_win, 2, 0, key_press, scrape);
	mlx_hook(ptr->mlx_win, 3, 0, key_release, scrape);
	mlx_hook(ptr->mlx_win, 6, 0, mouse_move_hook, scrape);
	mlx_hook(ptr->mlx_win, 17, 0, close_window, scrape);
	mlx_loop_hook(ptr->mlx, render_next_frame, scrape);
	mlx_loop(ptr->mlx);
}

void	mlx_warper(t_map_data *scrape)
{
	get_player_pos(scrape);
	window_init(scrape);
}
