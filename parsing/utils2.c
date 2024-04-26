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

void	tokens_reset(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		free(tmp->type);
		free(tmp->value);
		free(tmp);
	}
	*token = NULL;
}

void	exit_syntax_error(char *error_msg)
{
	printf("%s\n", error_msg);
}