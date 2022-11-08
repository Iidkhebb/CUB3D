/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidkhebb <iidkhebb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:07:23 by iidkhebb          #+#    #+#             */
/*   Updated: 2022/11/08 22:45:08 by iidkhebb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_text_val_extra(char *line, t_map_data **s, t_garbage **junk_list)
{
	if (!ft_strcmp("WE ", garbage(junk_list, ft_substr(line, 0, 3))))
	{
		(*s)->we = check_open(garbage(junk_list, ft_strtrim(&line[3], \
			WHITE_SPACES)), line);
	}
	else if (!ft_strcmp("EA ", garbage(junk_list, ft_substr(line, 0, 3))))
	{
		(*s)->ea = check_open(garbage(junk_list, ft_strtrim(&line[3], \
			WHITE_SPACES)), line);
	}
}

char	**init_tab(t_maplines **maplines, t_garbage **junk_list)
{
	char	**tab;

	tab = list_to_tab(*maplines);
	final_check(*maplines, tab, *junk_list);
	return (tab);
}

char	**check_map(int fd, t_maplines **maplines)
{
	t_garbage		*junk_list;
	char			*line;
	int				map_level;
	static char		*prv = NULL;
	int				is_done;

	is_done = 0;
	junk_list = NULL;
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		iter_extra(line, &junk_list, &map_level, is_done);
		if ((prv && check_empty_line(line)) || (prv && !line))
			is_done = 1;
		else if ((map_level == 454 || map_level == -1))
		{
			check_endline(is_done, line, &junk_list, maplines);
			prv = line;
		}
	}
	return (init_tab(maplines, &junk_list));
}
