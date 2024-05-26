#include "minishell.h"

char	*get_type1(char *line, int *i)
{
	if (line[*i] == '|')
		return ((*i)++, ft_strdup("PIPE"));
	else if (line[*i] == '<' && line[*i + 1] == '<')
		return ((*i)+=2, ft_strdup("HEREDOC"));
	else if (line[*i] == '>' && line[*i + 1] == '>')
		return ((*i)+=2, ft_strdup("APPEND"));
	else if (line[*i] == '<')
		return ((*i)++, ft_strdup("INPUT"));
	else if (line[*i] == '>')
		return ((*i)++, ft_strdup("OUTPUT"));
	else if (is_white(line[*i]))
	{
		while (is_white(line[*i]))
			(*i)++;
		return (ft_strdup("WHITE"));
	}
	else
		return (NULL);
}

char	*get_type2(char *line, int *i)
{
	char	*type;
	int		in_quote;
	char	quote;

	in_quote = 0;
	type = ft_strdup("WORD");
	while (line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			if (in_quote && line[*i] == quote)
				in_quote = 0;
			else if (!in_quote)
			{
				quote = line[*i];
				in_quote = 1;
			}
		}
		if (in_quote)
			(*i)++;
		else
		{
			if (is_in_word(line[*i]))
				(*i)++;
			else
				break;
		}
	}
	if (in_quote)
		exit_syntax_error("unclosed quotes syntax error");
	return (type);
}

void	init_token(t_token *new_token, char *line, int *i)
{
	char	*type;
	int		start;

	type = get_type1(line, i);
	if (type)
		new_token->value = ft_strdup("operator");
	else
	{
		start = *i;
		type = get_type2(line, i);
		new_token->value = ft_substr(line, start, (*i) - start);
	}
	new_token->type = type;
}

void	tokenize(t_token **token, char *line)
{
	int	i;
	t_token	*new_token;

	i = 0;
	while (line[i])
	{
		new_token = malloc(sizeof(t_token));
		init_token(new_token, line, &i);
		new_token->next = NULL;
		new_token->wh = 0;
		add_back(token, new_token);
	}
}
