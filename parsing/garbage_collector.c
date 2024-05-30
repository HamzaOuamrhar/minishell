#include "minishell.h"

void	garbage_collector(t_garbage **gr, void	*p)
{
	t_garbage	*tmp;
	t_garbage	*new_g;

	new_g = malloc(sizeof(t_garbage));
	new_g->next = NULL;
	new_g->p = p;
	if (!*gr)
		*gr = new_g;
	else
	{
		tmp = *gr;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_g;
	}
}

void	empty_garbage(t_garbage *gr)
{
	t_garbage	*tmp;
	while (gr)
	{
		tmp = gr->next;
		free(gr->p);
		free(gr);
		gr = tmp;
	}
}
