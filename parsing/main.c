#include "../minishell.h"

void wait_prompt1(t_parse *st)
{
	t_token		*token;
	t_params	params;

	token = NULL;
	params.status = 0;
	while (1)
	{
		params.q = 0;
		st->arr = readline("shellantics$ ");
		if (!st->arr)
			break ; // exit with 1
		add_history(st->arr);
		tokenize(&token, st->arr, &params.q);
		while (token)
		{
			printf("%s\n", token->value);
			token = token->next;
		}
		if (!params.q)
		{
			if (!syntax(token))
			{
				expander(token, params);
				parser(token, &st);
				// int i = 0;
				// print(&st);
				if (checking_cmd(st))
				{
					tokens_reset(&token);
					continue ;
				}
				st->com_path = get_acc_path(st->paths_array, st->cmd[0]);
				if (!st->path)
				{
					printf("Shellantics: %s: No such file or directory\n", st->cmd[0]);
					freeing2(st);
					tokens_reset(&token);
					continue ;
				}
				if (checking_cmd2(st))
				{
					free(st->com_path);
					tokens_reset(&token);
					continue ;
				}
				if (!st->com_path)
					printf("%s :command not found\n", st->cmd[0]);
				else
					excute_cmd(st);
			}
		}
		tokens_reset(&token);
	}
}
