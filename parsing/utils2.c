#include "minishell.h"

t_token	*last_node(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_back(t_token **token, t_token *new)
{
	if (!*token)
		*token = new;
	else
		last_node(*token)->next = new;
}

void	exit_syntax_error()
{
	perror("syntax error");
	exit(1);
}