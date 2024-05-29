#include "minishell.h"

void	valide_val(t_decl *decl, char **n_t_v, t_token **token)
{
	if (!is_white(decl->value[0]))
	{
		while (decl->value[decl->j] && !is_white(decl->value[decl->j]))
			decl->j++;
		if (!(*token)->flag && !decl->still)
			*n_t_v = ft_strjoin(*n_t_v, ft_substr(decl->value, 0, decl->j));
		else
		{
			if (decl->still)
				add_middle_n(token, ft_substr(decl->value, 0, decl->j));
			else
				(*token)->value = ft_strjoin((*token)->value,
						ft_substr(decl->value, 0, decl->j));
		}
		if (decl->value[decl->j] && no_rest(decl->value, decl->j))
			decl->still = 1;
		else
			decl->still = 0;
	}
	if (white_word(decl->value))
	{
		if (!(*n_t_v))
			*n_t_v = ft_strdup(decl->value);
		else
			add_middle_n(token, ft_strdup(decl->value));
	}
	else
	{
		if (!(*n_t_v))
		{
			first_word_pos(decl->value, &decl->i, &decl->j);
			*n_t_v = ft_substr(decl->value, decl->i, decl->j - decl->i);
		}
		add_middle(token, ft_split(decl->value + decl->j, ' ', &decl->still));
	}
	if (!(*token)->flag && word_count(decl->value) > 1)
		(*token)->flag = 1;
}

void	get_value(t_decl *decl, int *i, char *token_value)
{
	decl->j = 0;
	(*i)++;
	decl->first = *i;
	if (token_value[*i] && (!is_alph(token_value[*i])
			|| token_value[*i] != '_'))
		(*i)++;
	while (token_value[*i] && token_value[*i] != '$'
		&& (is_alph_num(token_value[*i]) || token_value[*i] == '_'))
		(*i)++;
	decl->value = getenv(ft_substr(token_value,
				decl->first, (*i) - decl->first));
}

void	set_value(char **n_t_v, char *token_value, int *i, t_token **token)
{
	t_decl	decl;

	decl.still = 0;
	while (token_value[*i])
	{
		if (token_value[*i] == '$')
		{
			get_value(&decl, i, token_value);
			if (!decl.value)
				*n_t_v = ft_strjoin(*n_t_v, "");
			else
				valide_val(&decl, n_t_v, token);
		}
		else
		{
			decl.first = *i;
			while (token_value[*i] && token_value[*i] != '$')
				(*i)++;
			if (!(*token)->flag && !decl.still)
				*n_t_v = ft_strjoin(*n_t_v, ft_substr(token_value,
							decl.first, *i - decl.first));
			else
				comp(decl, token, token_value, i);
		}
	}
}

void	non_quotes_expander(t_token **token)
{
	int		i;
	char	*n_t_v;
	t_token	*tmp;

	i = 0;
	n_t_v = NULL;
	tmp = *token;
	while ((*token)->value[i] && (*token)->value[i] != '$')
		i++;
	if (i)
		n_t_v = ft_substr((*token)->value, 0, i);
	if ((*token)->value[i])
		set_value(&n_t_v, (*token)->value, &i, token);
	tmp->value = n_t_v;
	if (white_word(tmp->value))
		tmp->wh = 1;
}

void	expander(t_token *token)
{
	while (token)
	{
		token->flag = 0;
		if (ft_strcmp(token->type, "WORD") == 0 && !token->here)
		{
			if (in_str(token->value, '\'') || in_str(token->value, '"'))
				quotes_expander(&token, token->value);
			else if (in_str(token->value, '$'))
				non_quotes_expander(&token);
		}
		else if (token->here)
			quotes_removal(token);
		token = token->next;
	}
}
