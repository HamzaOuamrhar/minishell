#include "minishell.h"

int	in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	set_value(char **new_token_value, char *token_value, int *i)
{
	char	*value;
	int		first;

	while (token_value[*i])
	{
		if (token_value[*i] == '$')
		{
			(*i)++;
			first = *i;
			while (token_value[*i] && token_value[*i] != '$' && (is_alph_num(token_value[*i]) || token_value[*i] == '_'))
				(*i)++;
			value = getenv(ft_substr(token_value, first, (*i) - first));
			if (!value)
				*new_token_value = ft_strjoin(*new_token_value, "");
			else
				*new_token_value = ft_strjoin(*new_token_value, value);
		}
		first = *i;
		while (token_value[*i] && token_value[*i] != '$')
			(*i)++;
		*new_token_value = ft_strjoin(*new_token_value, ft_substr(token_value, first, (*i) - first));
	}
}

void	quotes_expander(t_token *token)
{
	int	in_quote;
	int	i;
	char	quote;
	char	*new_token_value;
	int start;
	char	*value;

	new_token_value = NULL;
	in_quote = 0;
	i = 0;
	while (token->value[i])
	{
		if ((token->value[i] == '\'' || token->value[i] == '"') && !in_quote)
		{
			in_quote = 1;
			quote = token->value[i];
		}
		else if (in_quote && quote == token->value[i])
		{
			in_quote = 0;
			i += 1;
		}
		if (in_quote)
		{
			if (quote == '\'')
			{
				start = i;
				i += 1;
				while (token->value[i] && token->value[i] != '\'')
					i++;
				new_token_value = ft_strjoin(new_token_value, ft_substr(token->value, start, i - start + 1));
			}
			else
			{
				start = i;
				if (token->value[i] == '$')
				{
					i += 1;
					start = i;
					while (token->value[i] && (is_alph_num(token->value[i]) || token->value[i] == '_'))
						i++;
					value = getenv(ft_substr(token->value, start, i - start));
					if (value)
						new_token_value = ft_strjoin(new_token_value, value);
					else
						new_token_value = ft_strjoin(new_token_value, "");
					if (token->value[i] == '"')
						new_token_value = ft_strjoin(new_token_value, "\"");
				}
				else
				{
					i += 1;
					while (token->value[i] && token->value[i] != '"' && token->value[i] != '$')
						i++;
					if (token->value[i] == '$')
						new_token_value = ft_strjoin(new_token_value, ft_substr(token->value, start, i - start));
					else
						new_token_value = ft_strjoin(new_token_value, ft_substr(token->value, start, i - start + 1));
				}
			}
		}
		else
		{
			start = i;
			if (token->value[i] == '$')
			{
				i += 1;
				start = i;
				while (token->value[i] && (is_alph_num(token->value[i]) || token->value[i] == '_'))
					i++;
				value = getenv(ft_substr(token->value, start, i - start));
				if (value)
					new_token_value = ft_strjoin(new_token_value, value);
				else
					new_token_value = ft_strjoin(new_token_value, "");
			}
			else
			{
				while (token->value[i] && token->value[i] != '\'' && token->value[i] != '"' && token->value[i] != '$')
					i++;
				new_token_value = ft_strjoin(new_token_value, ft_substr(token->value, start, i - start));
			}
		}
	}
	token->value = new_token_value;
}

void	non_quotes_expander(t_token *token)
{
	int	i;
	char	*new_token_value;

	i = 0;
	while (token->value[i] && token->value[i] != '$')
		i++;
	new_token_value = ft_substr(token->value, 0, i);
	if (token->value[i])
		set_value(&new_token_value, token->value, &i);
	token->value = new_token_value;
}

void	expander(t_token *token)
{
	while (token)
	{
		if (ft_strncmp(token->type, "WORD", 4) == 0)
		{
			if (in_str(token->value, '\'') || in_str(token->value, '"'))
				quotes_expander(token);
			else if (in_str(token->value, '$'))
				non_quotes_expander(token);
		}
		token = token->next;
	}
}