#include "../minishell.h"

void	print(t_parse *parse)
{
	int	i;

	while (parse)
	{
		i = 0;
		printf("-------cmd------\n");
		while ((parse)->cmd[i])
		{
			printf("%s\n", (parse)->cmd[i]);
			i++;
		}
		i = 0;
		printf("-------files-------\n");
		while ((parse)->files)
		{
			printf("%s -> %d | amb: %d\n", (parse)->files->file, (parse)->files->type, (parse)->files->is_amb);
			(parse)->files = (parse)->files->next;
		}
		printf("---------in_dup------\n");
		if ((parse)->in_dup)
			printf("%s\n", (parse)->in_dup);
		printf("---------out_dup------\n");
		if ((parse)->out_dup)
			printf("%s\n", (parse)->out_dup);
		(parse) = (parse)->next;
		if ((parse))
		printf("**********next********\n");
	}
}