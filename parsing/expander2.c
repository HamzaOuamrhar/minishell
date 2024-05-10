#include "minishell.h"

void	get_var_key(char *token_value, int *i)
{
	if (token_value[*i] && !is_alph(token_value[*i])
		&& token_value[*i] != '_')
		(*i)++;
	else
		while (token_value[*i]
			&& (is_alph_num(token_value[*i]) || token_value[*i] == '_'))
			(*i)++;
}

void	set_value(char **new_tv, char *token_value, int *i, t_env *env_vars)
{
	char	*value;
	int		first;

	while (token_value[*i])
	{
		if (token_value[*i] == '$')
		{
			(*i)++;
			first = *i;
			get_var_key(token_value, i);
			value = get_env(ft_substr(token_value, first, (*i) - first),
					env_vars);
			if (!value)
				*new_tv = ft_strjoin(*new_tv, "");
			else
				*new_tv = ft_strjoin(*new_tv, value);
		}
		first = *i;
		while (token_value[*i] && token_value[*i] != '$')
			(*i)++;
		*new_tv = ft_strjoin(*new_tv,
				ft_substr(token_value, first, (*i) - first));
	}
}

void	non_quotes_expander(t_token *token, t_env *env_vars)
{
	int	i;
	char	*new_tv;

	i = 0;
	while (token->value[i] && token->value[i] != '$')
		i++;
	new_tv = ft_substr(token->value, 0, i);
	if (token->value[i])
		set_value(&new_tv, token->value, &i, env_vars);
	token->value = new_tv;
}
