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

void	redirection_syntax(t_token *token)
{
	int	error;

	error = 0;
	while (token)
	{
		if (ft_strncmp(token->type, "HEREDOC", 7) == 0 || ft_strncmp(token->type, "INPUT", 7) == 0)
		{
			if (token->next)
				if (ft_strncmp(token->next->type, "WHITE", 5) == 0)
					token = token->next;
			if (token->next)
			{
				token = token ->next;
				if (ft_strncmp(token->type, "INPUT", 5) == 0 || ft_strncmp(token->type, "OUTPUT", 6) == 0
					|| ft_strncmp(token->type, "APPEND", 6) == 0 || ft_strncmp(token->type, "HEREDOC", 5) == 0
						|| ft_strncmp(token->type, "PIPE", 4) == 0)
					error = 1;
			}
			else
				error = 1;
		}
		token = token->next;
	}
	if (error)
		exit_syntax_error("redirection syntax error");
}

void	syntax(t_token *token)
{
	quotes_syntax(token);
	redirection_syntax(token);
}