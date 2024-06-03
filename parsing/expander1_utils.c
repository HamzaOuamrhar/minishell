#include "../minishell.h"

void	comp(t_decl decl, t_token **token, char *token_value, int *i)
{
	if (decl.still)
		add_middle_n(token, ft_mysubstr(token_value,
				decl.first, *i - decl.first));
	else
		(*token)->value = ft_strjoin((*token)->value,
				ft_mysubstr(token_value, decl.first, *i - decl.first));
}

void	first_word_pos(char *value, int *i, int *j)
{
	int	k;

	k = 0;
	while (value[k] && is_white(value[k]))
		k ++;
	*i = k;
	while (value[k] && !is_white(value[k]))
		k ++;
	*j = k;
}
