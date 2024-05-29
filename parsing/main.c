#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *line;
	t_token	*token;
	t_env	*env_vars;
	t_parse	*parse;
	// int		i;

	(void)argc;
	(void)argv;
	token = NULL;
	env_vars = NULL;
	parse = NULL;
	set_env(&env_vars, env);
	while (1)
	{
		line = readline("___Shellantics => ");
		if (!line)
			break ;
		add_history(line);
		tokenize(&token, line);
		syntax(token);
		expander(token);
		while (token)
		{
			printf("%s\n",  token->value);
			token = token->next;
		}
		// parser(token, &parse);
		// while (parse)
		// {
		// 	i = 0;
		// 	// puts("-------cmd------");
		// 	// while (parse->cmd[i])
		// 	// {
		// 	// 	printf("%s\n", parse->cmd[i]);
		// 	// 	i++;
		// 	// }
		// 	// puts("\n");
		// 	// i = 0;
		// 	// puts("-------in-------\n");
		// 	// while (parse->in[i])
		// 	// {
		// 	// 	printf("%s\n", parse->in[i]);
		// 	// 	i++;
		// 	// }
		// 	// puts("\n");
		// 	// i = 0;
		// 	// puts("-------out-------\n");
		// 	// while (parse->out[i])
		// 	// {
		// 	// 	printf("%s\n", parse->out[i]);
		// 	// 	i++;
		// 	// }
		// 	// puts("\n");
		// 	// i = 0;
		// 	// puts("--------app-------\n");
		// 	// while (parse->app[i])
		// 	// {
		// 	// 	printf("%s\n", parse->app[i]);
		// 	// 	i++;
		// 	// }
		// 	// puts("\n");
		// 	// puts("---------in_dup------");
		// 	// if (parse->in_dup)
		// 	// 	printf("%s\n", parse->in_dup);
		// 	// puts("\n");
		// 	// puts("---------out_dup------");
		// 	// if (parse->out_dup)
		// 	// 	printf("%s\n", parse->out_dup);
		// 	parse = parse->next;
		// 	if (parse)
		// 	puts("**********next********");
		// }
		tokens_reset(&token);
	}
}
