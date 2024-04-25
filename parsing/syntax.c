#include "minishell.h"

void	quotes_syntax(t_token *token)
{
	int	error;

	error = 0;
	while (token)
	{
		error = 1;
		if (ft_strncmp(token->type, "DQUOTE", 6) == 0)
		{
			token = token->next;
			while (token && ft_strncmp(token->type, "DQUOTE", 6) != 0)
				token = token->next;
		}
		else if (ft_strncmp(token->type, "SQUOTE", 6) == 0)
		{
			token = token->next;
			while (token && ft_strncmp(token->type, "SQUOTE", 6) != 0)
				token = token->next;
		}
		if (token)
		{
			error = 0;
			token = token->next;
		}
	}
	if (error)
		exit_syntax_error("Unclosed quotes");
}

void	syntax(t_token *token)
{
	quotes_syntax(token);
}