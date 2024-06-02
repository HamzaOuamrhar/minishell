#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *line;
	t_token	*token;
	t_parse	*parse;
	int		q;

	(void)argc;
	(void)argv;
	(void)env;
	token = NULL;
	parse = NULL;
	while (1)
	{
		q = 0;
		line = readline("shellantics$ ");
		if (!line)
			break ;
		add_history(line);
		tokenize(&token, line, &q);
		if (!q)
		{
			if (!syntax(token))
			{
				expander(token);
				parser(token, &parse);
				print(&parse);
			}
		}
		free(line);
		tokens_reset(&token);
	}
	// ft_malloc(0, 3);
}
