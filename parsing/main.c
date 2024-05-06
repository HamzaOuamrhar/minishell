#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *line;
	t_token	*token;
	t_env	*env_vars;

	(void)argc;
	(void)argv;
	token = NULL;
	env_vars = NULL;
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
		while (token)
		{
			printf("%s:%s\n", token->value, token->type);
			token = token->next;
		}
		tokens_reset(&token);
	}
}
