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

void	outsize_quotes(int *i, char **new_tv, char *token_value, t_env *e_v)
{
	int		start;
	char	*value;

	start = *i;
	if (token_value[*i] == '$')
	{
		*i += 1;
		start = *i;
		get_var_key(token_value, i);
		value = get_env(ft_substr(token_value, start, *i - start), e_v);
		if (value)
			*new_tv = ft_strjoin(*new_tv, value);
		else
			*new_tv = ft_strjoin(*new_tv, "");
	}
	else
	{
		while (token_value[*i] && token_value[*i] != '\''
			&& token_value[*i] != '"' && token_value[*i] != '$')
			(*i)++;
		*new_tv = ft_strjoin(*new_tv,
				ft_substr(token_value, start, *i - start));
	}
}

void	inside_double_quotes(int *i, char *t_v, t_env *e_v, char **new_tv)
{
	int		start;
	char	*value;

	start = *i;
	if (t_v[*i] == '$')
	{
		*i += 1;
		start = *i;
		get_var_key(t_v, i);
		value = get_env(ft_substr(t_v, start, *i - start), e_v);
		if (value)
			*new_tv = ft_strjoin(*new_tv, value);
		else
			*new_tv = ft_strjoin(*new_tv, "");
		if (t_v[*i] == '"')
			*new_tv = ft_strjoin(*new_tv, "\"");
	}
	else
	{
		*i += 1;
		while (t_v[*i] && t_v[*i] != '"' && t_v[*i] != '$')
			(*i)++;
		if (t_v[*i] == '$')
			*new_tv = ft_strjoin(*new_tv, ft_substr(t_v, start, *i - start));
		else
			*new_tv = ft_strjoin(*new_tv, ft_substr(t_v, start, *i - start + 1));
	}
}

void	inside_single_quotes(int *i, char *t_v, char **new_tv)
{
	int	start;

	start = *i;
	*i += 1;
	while (t_v[*i] && t_v[*i] != '\'')
		(*i)++;
	*new_tv = ft_strjoin(*new_tv, ft_substr(t_v, start, *i - start + 1));
}

void	quotes_expander(t_token *token, t_env *e_v)
{
	int	in_quote;
	int	i;
	char	quote;
	char	*new_tv;

	new_tv = NULL;
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
				inside_single_quotes(&i, token->value, &new_tv);
			else
				inside_double_quotes(&i, token->value, e_v, &new_tv);
		}
		else
			outsize_quotes(&i, &new_tv, token->value, e_v);
	}
	token->value = new_tv;
}

void	expander(t_token *token, t_env *e_v)
{
	while (token)
	{
		if (ft_strncmp(token->type, "WORD", 4) == 0
			&& in_str(token->value, '$'))
		{
			if (in_str(token->value, '\'') || in_str(token->value, '"'))
				quotes_expander(token, e_v);
			else if (in_str(token->value, '$'))
				non_quotes_expander(token, e_v);
		}
		token = token->next;
	}
}
