#include "../../includes/cub3d.h"

t_maplines	*ft_lstnew_map(char *line)
{
	t_maplines	*new;

	new = (t_maplines *)malloc(sizeof(t_maplines));
	if (!(new))
		return (0);
	
	new->line = ft_strdup(line);
	// printf("%s", new->line);
	new->next = NULL;
	return (new);
}

t_maplines	*ft_lstlast_map(t_maplines *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_map(t_maplines **lst, t_maplines *new)
{
	t_maplines	*last_node;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast_map(*lst);
	last_node->next = new;
}

void	list_free_map(t_map_data **list)
{
	t_map_data	*l;
	int i;

	i = 0;
	l = *list;
	if (!l->map)
		return ;
	while (l->map[i])
		free(l->map[i++]);
	free(l->map[i]);
	free(l->map);
	i = 0;
	while (l->map_MINI[i])
		free(l->map_MINI[i++]);
	free(l->map_MINI[i]);
	free(l->map_MINI);
	free(l->NO);
	free(l->SO);
	free(l->WE);
	free(l->EA);
	free(l);
	return ;
}