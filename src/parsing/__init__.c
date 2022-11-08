/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __init__.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidkhebb <iidkhebb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:05:29 by iidkhebb          #+#    #+#             */
/*   Updated: 2022/11/08 22:07:13 by iidkhebb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	final_check( t_maplines *maplines, char **tab, t_garbage *junk_list)
{
	if (!check_walls(tab))
		return (ft_putstr_fd(ERR_MAPS_WALL, 2), list_free(&junk_list), \
			free_tab(tab), exit(1));
	list_free(&junk_list);
	free_list(maplines);
	return ;
}

int	check_endline(int is_done, char *line, \
	t_garbage **junk_list, t_maplines **maplines)
{
	if (is_done && !check_empty_line(line))
		return (ft_putstr_fd(ERR_MAPS_ENDLINE, 2), \
			list_free(junk_list), free_list(*maplines), exit(1), 0);
	if (line)
		ft_lstadd_back_map(maplines, ft_lstnew_map(line));
	return (1);
}

void	iter_line(char *line, t_garbage **junk_list, int *map_level)
{
	char	*trim;

	trim = ft_strtrim(line, WHITE_SPACES);
	garbage(junk_list, trim);
	*map_level = valid_texture(trim);
}

void	check_text_key(t_garbage **junk_list, int map_level)
{
	if (!map_level)
		return (ft_putstr_fd(ERR_TEXTURES_KEY, 2), \
			list_free(junk_list), exit(1));
}

void	iter_extra(char *line, t_garbage **junk_list, \
	int *map_level, int is_done)
{
	garbage(junk_list, line);
	if ((line && check_empty_line(line) \
		&& (*map_level != 454)) \
			|| (is_done && check_empty_line(line)))
	{
		return ;
	}
	iter_line(line, junk_list, map_level);
	check_text_key(junk_list, *map_level);
	return ;
}
