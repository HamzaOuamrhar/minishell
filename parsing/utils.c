#include "minishell.h"

char*	get_type(char *token)
{
	if (ft_strncmp("'", token, 10) == 0)
		return ("single");
	else if (ft_strncmp("\"", token, 10) == 0)
		return ("double");
	else if (ft_strncmp("<", token, 10) == 0)
		return (ft_strdup("input"));
	else if (ft_strncmp(">", token, 10) == 0)
		return (ft_strdup("output"));
	else if (ft_strncmp("<<", token, 10) == 0)
		return (ft_strdup("heredoc"));
	else if (ft_strncmp(">>", token, 10) == 0)
		return (ft_strdup("append"));
	else if (ft_strncmp("|", token, 10) == 0)
		return (ft_strdup("pipe"));
	else if (ft_strncmp("$", token, 10) == 0)
		return (ft_strdup("dollar"));
	else
		return (ft_strdup("word"));
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
		new_parse->next = NULL;
		add_back(parse, new_parse);
		i++;
	}
}