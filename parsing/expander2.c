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

void	is_in_quote(t_decl2 *decl, char *t_v)
{
	decl->z = 0;
	if ((t_v[decl->i] == '\'' || t_v[decl->i] == '"') && !decl->in_quote)
	{
		decl->in_quote = 1;
		decl->quote = t_v[decl->i];
		decl->i++;
	}
	else if (decl->in_quote && decl->quote == t_v[decl->i])
	{
		decl->i += 1;
		decl->in_quote = 0;
	}
}

void	inside_single_quote(t_decl2 *decl, t_token **token, char *t_v)
{
	decl->start = decl->i;
	while (t_v[decl->i] && t_v[decl->i] != '\'')
		decl->i++;
	if (!(*token)->flag && !decl->still)
		decl->n_t_v = ft_strjoin(decl->n_t_v, ft_substr(t_v, decl->start, decl->i - decl->start));
	else
	{
		if (decl->still)
			add_middle_n(token, ft_substr(t_v, decl->start, decl->i - decl->start));
		else
			(*token)->value = ft_strjoin((*token)->value, ft_substr(t_v, decl->start, decl->i - decl->start));
	}
}

void	out_quotes_not_key(t_decl2 *decl, char *t_v, t_token **token)
{
	decl->start = decl->i;
	while (t_v[decl->i] && t_v[decl->i] != '\'' && t_v[decl->i] != '"' && t_v[decl->i] != '$')
		decl->i++;
	if (!(*token)->flag && !decl->still)
		decl->n_t_v = ft_strjoin(decl->n_t_v, ft_substr(t_v, decl->start, decl->i - decl->start));
	else
	{
		if (decl->still)
			add_middle_n(token, ft_substr(t_v, decl->start, decl->i - decl->start));
		else
			(*token)->value = ft_strjoin((*token)->value, ft_substr(t_v, decl->start, decl->i - decl->start));
	}
}

void	double_quote_key(t_decl2 *decl, char *t_v)
{
	decl->i += 1;
	decl->start = decl->i;
	while (t_v[decl->i] && (is_alph_num(t_v[decl->i]) || t_v[decl->i] == '_'))
		decl->i++;
	decl->value = getenv(ft_substr(t_v, decl->start, decl->i - decl->start));
	if (decl->value)
		decl->n_t_v = ft_strjoin(decl->n_t_v, decl->value);
	else
		decl->n_t_v = ft_strjoin(decl->n_t_v, "");
}

void	out_quotes(t_decl2 *decl, char *t_v, t_token **token)
{
	decl->start = decl->i;
	if (t_v[decl->i] == '$')
	{
		decl->z = 0;
		decl->i += 1;
		decl->start = decl->i;
		if (t_v[decl->i] && (!is_alph(t_v[decl->i]) || t_v[decl->i] != '_'))
			decl->i++;
		while (t_v[decl->i] && (is_alph_num(t_v[decl->i]) || t_v[decl->i] == '_'))
			decl->i++;
		decl->value = getenv(ft_substr(t_v, decl->start, decl->i - decl->start));
		if (decl->value)
		{
			if (!is_white(decl->value[0]))
			{
				while (decl->value[decl->z] && !is_white(decl->value[decl->z]))
					decl->z++;
				if (!(*token)->flag && !decl->still)
				{
					decl->n_t_v = ft_strjoin(decl->n_t_v, ft_substr(decl->value, 0, decl->z));
				}
				else
				{
					if (decl->still)
						add_middle_n(token, ft_substr(decl->value, 0, decl->z));
					else
						(*token)->value = ft_strjoin((*token)->value, ft_substr(decl->value, 0, decl->z));
				}
				if (decl->value[decl->z] && no_rest(decl->value, decl->z))
					decl->still = 1;
				else
					decl->still = 0;
			}
			if (white_word(decl->value)){
				add_middle_n(token, ft_strdup(decl->value));
			}
			else
			{
				add_middle(token, ft_split(decl->value + decl->z, ' ', &decl->still));
			}
			if (!(*token)->flag && word_count(decl->value) > 1)
				(*token)->flag = 1;
		}
		else
		{
			decl->n_t_v = ft_strjoin(decl->n_t_v, "");
		}
	}
	else
		out_quotes_not_key(decl, t_v, token);
}

void	quotes_expander(t_token **token, char *t_v)
{
	t_decl2	decl;
	t_token	*tmp;

	decl.n_t_v = NULL;
	decl.in_quote = 0;
	decl.i = 0;
	decl.j = 0;
	decl.still = 0;
	tmp = *token;
	while (t_v[decl.i])
	{
		is_in_quote(&decl, t_v);
		if (decl.in_quote)
		{
			if (decl.quote == '\'')
				inside_single_quote(&decl, token, t_v);
			else
			{
				if (t_v[decl.i] == '$')
					double_quote_key(&decl, t_v);
				else
				{
					decl.start = decl.i;
					while (t_v[decl.i] && t_v[decl.i] != '"' && t_v[decl.i] != '$')
						decl.i++;
					if (!(*token)->flag && !decl.still)
						decl.n_t_v = ft_strjoin(decl.n_t_v, ft_substr(t_v, decl.start, decl.i - decl.start));
					else
					{
						if (decl.still)
								add_middle_n(token, ft_substr(t_v, decl.start, decl.i - decl.start));
						else
							(*token)->value = ft_strjoin((*token)->value, ft_substr(t_v, decl.start, decl.i - decl.start));
					}
				}
			}
		}
		else
			out_quotes(&decl, t_v, token);
	}
	tmp->value = decl.n_t_v;
}
