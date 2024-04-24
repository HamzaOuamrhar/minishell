#include "minishell.h"

t_parse	*last_node(t_parse *parse)
{
	t_parse	*tmp;

	tmp = parse;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_back(t_parse **parse, t_parse *new)
{
	if (!*parse)
		*parse = new;
	else
		last_node(*parse)->next = new;
}

void	exit_syntax_error()
{
	perror("syntax error");
	exit(1);
}