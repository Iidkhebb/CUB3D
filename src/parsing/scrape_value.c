/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrape_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidkhebb <iidkhebb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:16:49 by iidkhebb          #+#    #+#             */
/*   Updated: 2022/11/08 22:20:22 by iidkhebb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_textures_val(char *line, t_map_data **scrape, t_garbage **junk_list)
{
	t_map_data	*s;

	if (!line)
		return (1);
	s = *scrape;
	if (!ft_strcmp("NO ", garbage(junk_list, ft_substr(line, 0, 3))))
	{
		s->no = check_open(garbage(junk_list, ft_strtrim(&line[3], \
			WHITE_SPACES)), line);
	}
	else if (!ft_strcmp("SO ", garbage(junk_list, ft_substr(line, 0, 3))))
	{
		s->so = check_open(garbage(junk_list, ft_strtrim(&line[3], \
			WHITE_SPACES)), line);
	}
	else
	{
		get_text_val_extra(line, &s, junk_list);
	}
	return (1);
}

int	*process_rgb_data_extra(char **rgb)
{
	static int	out[3];

	out[0] = ft_atoi(rgb[0]);
	out[1] = ft_atoi(rgb[1]);
	out[2] = ft_atoi(rgb[2]);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	if (!(range(out[0]) && range(out[1]) && range(out[2])))
	{
		ft_putstr_fd(ERR_RGB_RNG, 2);
		exit(FAILED);
	}
	return (out);
}

int	*process_rgb_data(char *line, t_map_data **scrape)
{
	char	**rgb;
	int		len;

	if (count_char(line, ',') != 2)
	{
		free(line);
		free(*scrape);
		ft_putstr_fd(ERR_RGB_RNG, 2);
		exit(FAILED);
	}
	rgb = ft_split(line, ',');
	len = (double_array_len(rgb));
	if (!rgb || !rgb[2] || !rgb[1] || !rgb[0] || len != 3)
	{
		free(line);
		free(*scrape);
		ft_putstr_fd(ERR_RGB_RNG, 2);
		exit(FAILED);
	}
	return (process_rgb_data_extra(rgb));
}

int	get_rgb_val(char *line, t_map_data **scrape, t_garbage **junk_list)
{
	int			*rgb;
	t_map_data	*s;

	if (!line)
		return (1);
	s = *scrape;
	if (!ft_strcmp("C ", garbage(junk_list, ft_substr(line, 0, 2))))
	{
		rgb = process_rgb_data(garbage(junk_list, \
			ft_strtrim(garbage(junk_list, ft_substr(&line[2], 0, \
				ft_strlen(&line[2]) - 1)), WHITE_SPACES)), scrape);
		s->c[0] = rgb[0];
		s->c[1] = rgb[1];
		s->c[2] = rgb[2];
	}
	else if (!ft_strcmp("F ", garbage(junk_list, ft_substr(line, 0, 2))))
	{
		rgb = process_rgb_data(garbage(junk_list, \
			ft_strtrim(garbage(junk_list, ft_substr(&line[2], 0, \
				ft_strlen(&line[2]) - 1)), WHITE_SPACES)), scrape);
		s->f[0] = rgb[0];
		s->f[1] = rgb[1];
		s->f[2] = rgb[2];
	}
	return (1);
}

t_map_data	*scraper(int fd, char **raw_map)
{
	char		*line;
	t_garbage	*junk_list;
	t_map_data	*scrape;

	junk_list = NULL;
	line = "";
	scrape = (t_map_data *)malloc(sizeof(t_map_data));
	if (!scrape)
		return (0);
	while (line)
	{
		line = get_next_line(fd);
		garbage(&junk_list, line);
		if ((line && check_empty_line(line)))
			continue ;
		line = ft_strtrim(line, WHITE_SPACES);
		garbage(&junk_list, line);
		get_textures_val(line, &scrape, &junk_list);
		get_rgb_val(line, &scrape, &junk_list);
	}
	list_free(&junk_list);
	scrape->map = convert_map(raw_map);
	scrape->map_mini = convert_map(raw_map);
	return (scrape);
}
