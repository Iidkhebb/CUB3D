#include "../../includes/cub3d.h"

int check_empty_line(char *line)
{
    int i;

    i = 0;
    if (ft_strlen(line) == 0 || line[0] == '\n')
		return 1;
	return (0);
}


t_garbage	*ft_lstnew(char *junk)
{
	t_garbage	*new;

	new = (t_garbage *)malloc(sizeof(t_garbage));
	if (!(new))
		return (0);
	
	new->garbage_lines = junk;
	new->next = NULL;
	return (new);
}

t_garbage	*ft_lstlast(t_garbage *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_garbage **lst, t_garbage *new)
{
	t_garbage	*last_node;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast(*lst);
	last_node->next = new;
}

void	list_free(t_garbage **list)
{
	t_garbage	*tmp;
	t_garbage	*l;

	
	l = *list;
	if (!l)
		return ;
	while (l)
	{
		tmp = l->next;
		if (*l->garbage_lines)
		{
			free(l->garbage_lines);
		}
		free(l);
		l = tmp;
	}
	*list = NULL;
	return ;
}