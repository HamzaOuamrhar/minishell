#include "../minishell.h"

void	parser_reset(t_parse **st, t_token **token)
{
	while (*st)
	{
		if ((*st)->in_fd)
			close((*st)->in_fd);
		(*st) = (*st)->next;
	}
	*st = NULL;
	*token = NULL;
}

void	wait_prompt1(t_params *params)
{
	t_token		*token;
	t_parse		*st;
	token = NULL;
	st = NULL;
	params->status = 0;
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
					parser_reset(&st, &token);
					ft_malloc(0, 3);
					free(params->line);
					continue ;
				}
				st->com_path = get_acc_path(params->paths_array, st->cmd[0]);
				if (!params->path)
				{
					printf("Shellantics: %s: No such file or directory\n", st->cmd[0]);
					parser_reset(&st, &token);
					ft_malloc(0, 3);
					free(params->line);
					continue ;
				}
				if (checking_cmd2(st, params))
				{
					parser_reset(&st, &token);
					ft_malloc(0, 3);
					free(params->line);
					continue ;
				}
				if (!st->com_path)
					printf("%s :command not found\n", st->cmd[0]);
				else
					excute_cmd(st, params);
			}
		}
		parser_reset(&st, &token);
		ft_malloc(0, 3);
		free(params->line);
	}
}
