#include "includes/cub3d.h"

int main(int ac, char *av[])
{
    int fd; 
    t_map_data *scrape;
    t_map_data *tmp;
    char **map;

    map =  check_map(basic_init(ac, av));
 
    scrape = scraper(basic_init(ac, av), map);
    tmp = scrape;


    mlx_warper(scrape);
    list_free_map(&scrape);
    free(tmp);
    // system("leaks cub3D");
    return (0);
}
