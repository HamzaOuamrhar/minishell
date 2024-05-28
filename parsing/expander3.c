#include "minishell.h"

void	comp(t_decl decl, t_token **token, char *token_value, int *i)
{
	if (decl.still)
		add_middle_n(token, ft_substr(token_value,
				decl.first, *i - decl.first));
	else
		(*token)->value = ft_strjoin((*token)->value,
				ft_substr(token_value, decl.first, *i - decl.first));
}
