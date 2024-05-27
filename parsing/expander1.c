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
		if (token_value[*i] == '$')
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
					{
						puts("one");
						*new_token_value = ft_strjoin(*new_token_value, ft_substr(value, 0, j));
					}
					else
					{
						if (still)
						{
							puts("two");
							add_middle_n(&token, ft_substr(value, 0, j));
						}
						else
						{
							puts("three");
							token->value = ft_strjoin(token->value, ft_substr(value, 0, j));
						}
					}
					if (value[j] && no_rest(value, j))
						still = 1;
					else
						still = 0;
				}
				if (white_word(value))
						add_middle_n(&token, ft_strdup(value));
				else
				{
					puts("five");
					add_middle(&token, ft_split(value + j, ' ', &still));
				}
				if (!token->flag && word_count(value) > 1)
					token->flag = 1;
			}
		}
		else
		{
			puts("six");
			first = *i;
			while (token_value[*i] && token_value[*i] != '$')
				(*i)++;
			if (!token->flag && !still)
				*new_token_value = ft_strjoin(*new_token_value, ft_substr(token_value, first, *i - first));
			else
			{
				if (still)
					add_middle_n(&token, ft_substr(token_value, first, *i - first));
				else
					token->value = ft_strjoin(token->value, ft_substr(token_value, first, *i - first));
			}
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
	int		z;
	int		still;
	t_token	*tmp;

	new_token_value = NULL;
	in_quote = 0;
	i = 0;
	j = 0;
	still = 0;
	tmp = token;
	while (tmp->value[i])
	{
		z = 0;
		if ((tmp->value[i] == '\'' || tmp->value[i] == '"') && !in_quote)
		{
			in_quote = 1;
			quote = tmp->value[i];
			i++;
		}
		else if (in_quote && quote == tmp->value[i])
		{
			i += 1;
			in_quote = 0;
		}
		if (in_quote)
		{
			puts("in_quote");
			if (quote == '\'')
			{
				start = i;
				while (tmp->value[i] && tmp->value[i] != '\'')
					i++;
				new_token_value = ft_strjoin(new_token_value, ft_substr(tmp->value, start, i - start));
			}
			else
			{
				if (tmp->value[i] == '$')
				{
					puts("no");
					i += 1;
					start = i;
					while (tmp->value[i] && (is_alph_num(tmp->value[i]) || tmp->value[i] == '_'))
						i++;
					value = getenv(ft_substr(tmp->value, start, i - start));
					if (value)
						new_token_value = ft_strjoin(new_token_value, value);
					else
						new_token_value = ft_strjoin(new_token_value, "");
				}
				else
				{
					puts("yes3");
					start = i;
					while (tmp->value[i] && tmp->value[i] != '"' && tmp->value[i] != '$')
						i++;
					if (!token->flag && !still)
						new_token_value = ft_strjoin(new_token_value, ft_substr(tmp->value, start, i - start));
					else
					{
						if (still)
								add_middle_n(&token, ft_substr(tmp->value, start, i - start));
						else
							token->value = ft_strjoin(token->value, ft_substr(tmp->value, start, i - start));
					}
				}
			}
		}
		else
		{
			puts("not quote");
			start = i;
			if (tmp->value[i] == '$')
			{
				z = 0;
				i += 1;
				start = i;
				if (tmp->value[i] && (!is_alph(tmp->value[i]) || tmp->value[i] != '_'))
					i++;
				while (tmp->value[i] && (is_alph_num(tmp->value[i]) || tmp->value[i] == '_'))
					i++;
				value = getenv(ft_substr(tmp->value, start, i - start));
				if (value)
				{
					if (!is_white(value[0]))
					{
						while (value[z] && !is_white(value[z]))
							z++;
						if (!token->flag && !still)
						{
							puts("yes1");
							new_token_value = ft_strjoin(new_token_value, ft_substr(value, 0, z));
						}
						else
						{
							puts("not1");
							if (still)
								add_middle_n(&token, ft_substr(value, 0, z));
							else
								token->value = ft_strjoin(token->value, ft_substr(value, 0, z));
						}
						if (value[z] && no_rest(value, z))
							still = 1;
						else
							still = 0;
					}
					if (white_word(value)){
						puts("not2");
						add_middle_n(&token, ft_strdup(value));
					}
					else
					{
						puts("yes2");
						add_middle(&token, ft_split(value + z, ' ', &still));
					}
					if (!token->flag && word_count(value) > 1)
						token->flag = 1;
				}
				else
				{
					puts("not3");
					new_token_value = ft_strjoin(new_token_value, "");
				}
			}
			else
			{
				puts("not4");
				while (tmp->value[i] && tmp->value[i] != '\'' && tmp->value[i] != '"' && tmp->value[i] != '$')
					i++;
				if (i)
					new_token_value = ft_strjoin(new_token_value, ft_substr(tmp->value, start, i - start));
			}
		}
	}
	tmp->value = new_token_value;
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