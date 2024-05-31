#include "minishell.h"

int	redirection_syntax(t_token *token)
{
	int	error;
	t_token *tmp;

	error = 0;
	while (token)
	{
		if (ft_strcmp(token->type, "HEREDOC") == 0 || ft_strcmp(token->type, "INPUT") == 0
			|| ft_strcmp(token->type, "OUTPUT") == 0 || ft_strcmp(token->type, "APPEND") == 0)
		{
			tmp = token;
			if (token->next)
				if (ft_strcmp(token->next->type, "WHITE") == 0)
					token = token->next;
			if (token->next)
			{
				token = token ->next;
				if (ft_strcmp(token->type, "INPUT") == 0 || ft_strcmp(token->type, "OUTPUT") == 0
					|| ft_strcmp(token->type, "APPEND") == 0 || ft_strcmp(token->type, "HEREDOC") == 0
						|| ft_strcmp(token->type, "PIPE") == 0)
					error = 1;
				else
				{
					if (ft_strcmp(tmp->type, "HEREDOC") == 0)
						token->here = 1;
				}
			}
			else
				error = 1;
		}
		token = token->next;
	}
	if (error)
	{
		exit_syntax_error("redirection syntax error");
		return (1);
	}
	return (0);
}

int	pipe_syntax(t_token *token)
{
	int	error;

	error = 0;
	if (token && ft_strcmp(token->type, "WHITE") == 0)
		token = token->next;
	if (token && ft_strcmp(token->type, "PIPE") == 0)
	{
		exit_syntax_error("syntax error near unexpected token `|'");
		return (1);
	}
	while (token)
	{
		if (ft_strcmp(token->type, "PIPE") == 0)
		{
			error = 1;
			if (!token->next)
				break ;
			token = token->next;
			while (token)
			{
				if (ft_strcmp(token->type, "WHITE") != 0 && ft_strcmp(token->type, "PIPE") != 0)
				{
					error = 0;
					break ;
				}
				token = token->next;
			}
		}
		if (token)
			token = token->next;
	}
	if (error)
	{
		exit_syntax_error("syntax error near unexpected token `|'");
		return (1);
	}
	return (0);
}

int	syntax(t_token *token)
{
	if (pipe_syntax(token))
		return (1);
	if (redirection_syntax(token))
		return (1);
	return (0);
}