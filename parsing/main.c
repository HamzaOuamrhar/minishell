#include "../minishell.h"

void	parser_reset(t_parse **st)
{
	while (*st)
	{
		if ((*st)->in_fd)
			close((*st)->in_fd);
		(*st) = (*st)->next;
}

void	wait_prompt1(t_params *params)
{
	t_token		*token;
	t_parse		*st;
	bool		pipes;
	int			i;

	token = NULL;
	i = 0;
	st = NULL;
	pipes = true;
	params->status = 0; //remember the last word on the "_" env
	while (1)
	{
		params->q = 0;
		params->line = readline("• Shellantics$ ");
		if (!params->line)
			break ; // exit with 1
		add_history(params->line);
		tokenize(&token, params->line, &params->q);
		if (!params->q)
		{
			if (!syntax(token))
			{
				expander(token, *params);
				parser(token, &st, params);
				if (checking_cmd(st, params))
				{
					tokens_reset(&token);
					parser_reset(&st);
					continue ;
				}
				st->com_path = get_acc_path(params->paths_array, st->cmd[0]);
				if (!params->path)
				{
					printf("Shellantics: %s: No such file or directory\n", st->cmd[0]);
					tokens_reset(&token);
					parser_reset(&st);
					continue ;
				}
				if (checking_cmd2(st, params))
				{
					tokens_reset(&token);
					parser_reset(&st);
					continue ;
				}
				if (!st->com_path)
					printf("%s :command not found\n", st->cmd[0]);
				else
					excute_cmd(st, params);
			}
		}
		tokens_reset(&token);
		parser_reset(&st);
	}
}
