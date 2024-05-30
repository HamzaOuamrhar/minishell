#include "minishell.h"

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
		decl->n_t_v = ft_strjoin(decl->n_t_v,
				ft_substr(t_v, decl->start, decl->i - decl->start));
	else
	{
		if (decl->still)
			add_middle_n(token,
				ft_substr(t_v, decl->start, decl->i - decl->start));
		else
			(*token)->value = ft_strjoin((*token)->value,
					ft_substr(t_v, decl->start, decl->i - decl->start));
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

void	inside_quotes(t_decl2 *decl, char *t_v, t_token **token)
{
	if (decl->quote == '\'')
		inside_single_quote(decl, token, t_v);
	else
	{
		if (t_v[decl->i] == '$')
			double_quote_key(decl, t_v);
		else
		{
			decl->start = decl->i;
			while (t_v[decl->i] && t_v[decl->i] != '"' && t_v[decl->i] != '$')
				decl->i++;
			if (!(*token)->flag && !decl->still)
				decl->n_t_v = ft_strjoin(decl->n_t_v,
						ft_substr(t_v, decl->start, decl->i - decl->start));
			else
			{
				if (decl->still)
					add_middle_n(token, ft_substr(t_v,
							decl->start, decl->i - decl->start));
				else
					(*token)->value = ft_strjoin((*token)->value,
							ft_substr(t_v, decl->start, decl->i - decl->start));
			}
		}
	}
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
			inside_quotes(&decl, t_v, token);
		else
			out_quotes(&decl, t_v, token);
	}
	tmp->value = decl.n_t_v;
	if (white_word(tmp->value))
	{
		tmp->flag = 1;
		tmp->wh = 1;
	}
}
