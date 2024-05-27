#include "minishell.h"

void	redirection_syntax(t_token *token)
{
	int	error;

	error = 0;
	while (token)
	{
		if (ft_strncmp(token->type, "HEREDOC", 7) == 0 || ft_strncmp(token->type, "INPUT", 7) == 0
			|| ft_strncmp(token->type, "OUTPUT", 6) == 0 || ft_strncmp(token->type, "APPEND", 6) == 0)
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
				else
					token->here = 1;
			}
			else
				error = 1;
		}
		token = token->next;
	}
	if (error)
		exit_syntax_error("redirection syntax error");
}

void	pipe_syntax(t_token *token)
{
	int	error;

	error = 0;
	if (token && ft_strcmp(token->type, "WHITE") == 0)
		token = token->next;
	if (token && ft_strncmp(token->type, "PIPE", 4) == 0)
		exit_syntax_error("syntax error near unexpected token `|'");
	while (token)
	{
		if (ft_strncmp(token->type, "PIPE", 4) == 0)
		{
			error = 1;
			if (!token->next)
				break ;
			token = token->next;
			while (token)
			{
				if (ft_strncmp(token->type, "WHITE", 5) != 0 && ft_strncmp(token->type, "PIPE", 4) != 0)
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
		exit_syntax_error("syntax error near unexpected token `|'");
}

void	syntax(t_token *token)
{
	pipe_syntax(token);
	redirection_syntax(token);
}