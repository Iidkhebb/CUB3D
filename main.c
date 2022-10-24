#include "includes/cub3d.h"

int main(int ac, char *av[])
{
    int fd; 
    t_map_data *scrape;

    check_map(basic_init(ac, av));
    scrape = scraper(basic_init(ac, av));
    
    // while (scrape->data)
    // {
    //     printf("%s", scrape->data->line);
    //     scrape->data = scrape->data->next;
    // }
    
    
    list_free_map(&scrape);
    free(scrape);

    // system("leaks cub3D");
    return (0);
}
