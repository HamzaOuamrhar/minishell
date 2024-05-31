#include "minishell.h"

void	quotes_removal(t_token *tokens)
{
	int		in_quote;
	char	quote;
	int		i;
	int		j;
	char	*new_value;

	in_quote = 0;
	i = 0;
	j = 0;
	if (ft_strcmp(tokens->type, "WORD") == 0 && (in_str(tokens->value, '\'') || in_str(tokens->value, '"')))
	{
		tokens->has_q = 1;
		new_value = ft_malloc(ft_strlen(tokens->value) + 1, 1);
		if (!new_value)
			return ;
		while (tokens->value[i])
		{
			if ((tokens->value[i] == '\'' || tokens->value[i] == '"') && !in_quote)
			{
				in_quote = 1;
				quote = tokens->value[i];
				i += 1;
			}
			else if (in_quote && tokens->value[i] == quote)
			{
				in_quote = 0;
				i += 1;
			}
			if (!in_quote)
			{
				while (tokens->value[i] && tokens->value[i] != '\'' && tokens->value[i] != '"')
				{
					new_value[j] = tokens->value[i];
					j++;
					i++;
				}
			}
			else
			{
				while (tokens->value[i] && tokens->value[i] != quote)
				{
					new_value[j] = tokens->value[i];
					j++;
					i++;
				}
			}
		}
		new_value[j] = '\0';
		tokens->value = new_value;
	}
	else
		tokens->has_q = 0;
}
