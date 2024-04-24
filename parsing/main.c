#include "minishell.h"

int main()
{
	char *line;
	t_parse	*parse;
	while (1)
	{
		line = readline("Shellantics$ ");
		if (!line)
			break ;
		if (line)
			add_history(line);
		parsing(&parse, line);
	}
}