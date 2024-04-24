#include "minishell.h"

int	in_str(char *str, char c, int *count)
{
	int	i;
	int	in;

	i = 0;
	in = 0;
	(*count) = 0;
	while(str[i])
	{
		if (str[i] == c)
		{
			in = 1;
			(*count)++;
		}
		i++;
	}
	return (in);
}

int	is_alph_num(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >='A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

int	is_word(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_alph_num(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valide_operator(char *s)
{
	if (ft_strncmp(s, "<<", 1) == 0 || ft_strncmp(s, ">>", 1) == 0)
		return (1);
	return (0);
}

char*	get_type(char *token)
{
	int	count;

	if (!in_str(token, '\'', &count) && !in_str(token, '"', &count) && is_word(token))
		return (ft_strdup("word"));
	else if (in_str(token, '\'', &count) && (token[0] == '\'') && (count % 2 == 0) && token[ft_strlen(token) - 1] == '\'')
		return (ft_strdup("word"));
	else if (in_str(token, '"', &count) && (token[0] == '"') && (count % 2 == 0) && token[ft_strlen(token) - 1] == '"')
		return (ft_strdup("word"));
	else
		if (valide_operator(token))
			return (ft_strdup("operator"));
	return (NULL);
}

void	parsing(t_parse **parse, char *line)
{
	t_parse *new_parse;
	char	**line_array;
	int		i;

	i = 0;
	line_array = ft_split(line, ' ');
	while (line_array[i])
	{
		new_parse = malloc(sizeof(t_parse));
		new_parse->type = get_type(line_array[i]);
		if (!new_parse->type)
			exit_syntax_error();
		new_parse->next = NULL;
		add_back(parse, new_parse);
		i++;
	}
}
