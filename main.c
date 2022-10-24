#include "includes/cub3d.h"

int main(int ac, char *av[])
{
    int fd; 
    t_map_data *scrape;

    check_map(basic_init(ac, av));
    scrape = scraper(basic_init(ac, av));

    free(scrape);
    system("leaks cub3D");
    return (0);
}
