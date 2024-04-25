#include "minishell.h"

int main()
{
	char *line;
	t_token	*token;

	token = NULL;
	while (1)
	{
		line = readline("Shellantics$ ");
		if (!line)
			break ;
		add_history(line);
		tokenize(&token, line);
		syntax(token);
		tokens_reset(&token);
	}
}
