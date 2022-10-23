#include "includes/cub3d.h"

int main(int ac, char *av[])
{
    t_map_data *scrape;
    int fd; 

    check_map(basic_init(ac, av));
    scraper(scrape, basic_init(ac, av));
    return (0);
}
