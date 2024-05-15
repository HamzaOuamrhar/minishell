#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *line;
	t_token	*token;
	t_env	*env_vars;
	t_parse	*parse;
	int		i;

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
		expander(token, env_vars);
		parser(token, &parse);
		while (parse)
		{
			i = 0;
			puts("-------cmd------\n");
			while (parse->cmd[i])
			{
				printf("%s\n", parse->cmd[i]);
				i++;
			}
			puts("\n");
			i = 0;
			puts("-------in-------\n");
			while (parse->in[i])
			{
				printf("%s\n", parse->in[i]);
				i++;
			}
			puts("\n");
			i = 0;
			puts("-------out-------\n");
			while (parse->out[i])
			{
				printf("%s\n", parse->out[i]);
				i++;
			}
			puts("\n");
			i = 0;
			puts("--------app-------\n");
			while (parse->app[i])
			{
				printf("%s\n", parse->app[i]);
				i++;
			}
			puts("\n");
			parse = parse->next;
			puts("******************");
		}
		tokens_reset(&token);
	}
}
