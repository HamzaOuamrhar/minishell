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

void	set_value(char **new_token_value, char *token_value, int *i, t_token *token)
{
	char	*value;
	int		first;
	int		j;
	int		still;

	still = 0;
	while (token_value[*i])
	{
		j = 0;
		(*i)++;
		first = *i;
		if (token_value[*i] && (!is_alph(token_value[*i]) || token_value[*i] != '_'))
			(*i)++;
		while (token_value[*i] && token_value[*i] != '$' && (is_alph_num(token_value[*i]) || token_value[*i] == '_'))
			(*i)++;
		value = getenv(ft_substr(token_value, first, (*i) - first));
		if (!value)
			*new_token_value = ft_strjoin(*new_token_value, "");
		else
		{
			if (!is_white(value[0]))
			{
				while (value[j] && !is_white(value[j]))
					j++;
				if (!token->flag && !still)
					*new_token_value = ft_strjoin(*new_token_value, ft_substr(value, 0, j));
				else
				{
					if (still)
						add_middle_n(&token, ft_substr(value, 0, j));
					else
						token->value = ft_strjoin(token->value, ft_substr(value, 0, j));
				}
				if (value[j] && no_rest(value, j))
					still = 1;
				else
					still = 0;
			}
			add_middle(&token, ft_split(value + j, ' ', &still));
			if (!token->flag && word_count(value) > 1)
				token->flag = 1;
		}
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
	int		j;

	new_token_value = NULL;
	in_quote = 0;
	i = 0;
	j = 0;
	while (token->value[i])
	{
		if ((token->value[i] == '\'' || token->value[i] == '"') && !in_quote)
		{
			in_quote = 1;
			quote = token->value[i];
			i++;
		}
		else if (in_quote && quote == token->value[i])
		{
			i += 1;
			in_quote = 0;
		}
		if (in_quote)
		{
			if (quote == '\'')
			{
				start = i;
				while (token->value[i] && token->value[i] != '\'')
					i++;
				new_token_value = ft_strjoin(new_token_value, ft_substr(token->value, start, i - start));
			}
			else
			{
				if (token->value[i] == '$')
				{
					i += 1;
					start = i;
					if (token->value[i] && (!is_alph(token->value[i]) || token->value[i] != '_'))
						i++;
					while (token->value[i] && (is_alph_num(token->value[i]) || token->value[i] == '_'))
						i++;
					value = getenv(ft_substr(token->value, start, i - start));
					if (value)
					{
						if (word_count(value) > 1)
						{
							token->flag = 1;
							if (!is_white(value[0]))
							{
								while (value[j] && !is_white(value[j]))
									j++;
							}
							new_token_value = ft_strjoin(new_token_value, ft_substr(value, 0, j));
							add_middle(&token, ft_split(value + j, ' ', NULL));
						}
						else
							new_token_value = ft_strjoin(new_token_value, value);
					}
					else
						new_token_value = ft_strjoin(new_token_value, "");
				}
				else
				{
					start = i;
					while (token->value[i] && token->value[i] != '"' && token->value[i] != '$')
						i++;
					new_token_value = ft_strjoin(new_token_value, ft_substr(token->value, start, i - start));
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
				if (token->value[i] && (!is_alph(token->value[i]) || token->value[i] != '_'))
					i++;
				while (token->value[i] && (is_alph_num(token->value[i]) || token->value[i] == '_'))
					i++;
				value = getenv(ft_substr(token->value, start, i - start));
				if (value)
				{
					if (word_count(value) > 1)
					{
						token->flag = 1;
						if (!is_white(value[0]))
						{
							while (value[j] && !is_white(value[j]))
								j++;
						}
						new_token_value = ft_strjoin(new_token_value, ft_substr(value, 0, j));
						add_middle(&token, ft_split(value + j, ' ', NULL));
					}
					else
						new_token_value = ft_strjoin(new_token_value, value);
				}
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
	new_token_value = NULL;
	while (token->value[i] && token->value[i] != '$')
		i++;
	if (i)
		new_token_value = ft_substr(token->value, 0, i);
	if (token->value[i])
		set_value(&new_token_value, token->value, &i, token);
	token->value = new_token_value;
}

void	expander(t_token *token)
{
	while (token)
	{
		token->flag = 0;
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