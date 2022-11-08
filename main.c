/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iidkhebb <iidkhebb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:42:52 by iidkhebb          #+#    #+#             */
/*   Updated: 2022/11/08 22:45:01 by iidkhebb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int ac, char *av[])
{
	t_map_data	*scrape;
	t_map_data	*tmp;
	t_maplines	*maplines;
	char		**map;

	maplines = NULL;
	map = check_map(basic_init(ac, av), &maplines);
	scrape = scraper(basic_init(ac, av), map);
	tmp = scrape;
	mlx_warper(scrape);
	list_free_map(&scrape);
	free(tmp);
	return (0);
}
