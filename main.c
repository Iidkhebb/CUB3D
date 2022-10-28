#include "includes/cub3d.h"

int main(int ac, char *av[])
{
    int fd; 
    t_map_data *scrape;
    t_map_data *tmp;

    if (check_map(basic_init(ac, av)))
        return 1;
    scrape = scraper(basic_init(ac, av));
    tmp = scrape;

    mlx_warper(scrape);
    list_free_map(&scrape);
    free(tmp);
    // system("leaks cub3D");
    return (0);
}
