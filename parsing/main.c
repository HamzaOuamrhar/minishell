#include "minishell.h"

int main()
{
	char *line;
	t_token	*token;
	while (1)
	{
		line = readline("Shellantics$ ");
		if (!line)
			break ;
		if (line)
			add_history(line);
		tokenize(&token, line);
		syntax(token);
	}
}
