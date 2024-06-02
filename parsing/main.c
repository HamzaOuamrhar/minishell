#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_token		*token;
	t_parse		*parse;
	t_params	params;

	(void)argc;
	(void)argv;
	(void)env;
	token = NULL;
	parse = NULL;
	params.status = 0;
	while (1)
	{
		params.q = 0;
		params.line = readline("shellantics$ ");
		if (!params.line)
			break ;
		add_history(params.line);
		tokenize(&token, params.line, &params.q);
		if (!params.q)
		{
			if (!syntax(token))
			{
				expander(token, params);
				parser(token, &parse);
				print(&parse);
			}
		}
		free(params.line);
		tokens_reset(&token);
	}
	// ft_malloc(0, 3);
}
