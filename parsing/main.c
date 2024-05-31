#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *line;
	t_token	*token;
	t_parse	*parse;
	int		i;

	(void)argc;
	(void)argv;
	(void)env;
	token = NULL;
	parse = NULL;
	while (1)
	{
		line = readline("___Shellantics => ");
		if (!line)
			break ;
		add_history(line);
		tokenize(&token, line);
		syntax(token);
		expander(token);
		parser(token, &parse);
		while (parse)
		{
			i = 0;
			printf("-------cmd------\n");
			while (parse->cmd[i])
			{
				printf("%s\n", parse->cmd[i]);
				i++;
			}
			printf("\n");
			i = 0;
			printf("-------in-------\n");
			while (parse->in[i])
			{
				printf("%s\n", parse->in[i]);
				i++;
			}
			printf("\n");
			i = 0;
			printf("-------out-------\n");
			while (parse->out[i])
			{
				printf("%s\n", parse->out[i]);
				i++;
			}
			printf("\n");
			i = 0;
			printf("--------app-------\n");
			while (parse->app[i])
			{
				printf("%s\n", parse->app[i]);
				i++;
			}
			printf("\n");
			printf("---------in_dup------\n");
			if (parse->in_dup)
				printf("%s\n", parse->in_dup);
			printf("\n");
			printf("---------out_dup------\n");
			if (parse->out_dup)
				printf("%s\n", parse->out_dup);
			parse = parse->next;
			if (parse)
			printf("**********next********");
		}
		free(line);
		// tokens_reset(&token);
	}
	ft_malloc(0, 3);
}
