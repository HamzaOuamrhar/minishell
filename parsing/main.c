#include "../minishell.h"

void	parser_reset(t_parse **st)
{
	while (*st)
	{
		if ((*st)->in_fd)
			close((*st)->in_fd);
		(*st) = (*st)->next;
	}
}

void	slash_path(t_parse *st, t_params *params)
{
	// printf("[%s]\n", st->cmd[0]);
	if (access(st->cmd[0], X_OK))
		st->com_path = get_acc_path(params->paths_array, st->cmd[0]);
	else
		st->com_path = ft_copy(st->cmd[0]);
}

void	wait_prompt1(t_params *params)
{
	t_token		*token;
	t_parse		*st;
	int			i;
	static int stdin_copy;
   	static int stdout_copy;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);

	token = NULL;
	i = 0;
	st = NULL;
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
				params->cmds = lstsize(st);
				while (st)
				{
					if (checking_cmd(st, params))
					{
						tokens_reset(&token);
						parser_reset(&st);
						continue ;
					}
					slash_path(st, params);
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
						excute_cmd(st, params, i);
					st = st->next;
					i++;
				}
				if (i == params->cmds)
				{
					if (dup2(stdin_copy, 0) == -1 || (dup2(stdout_copy, 1) == -1))
					{
						puts ("error in dup func");
						return 1;
					}
        			
				}
				i = 0;
			}
		}
		tokens_reset(&token);
		parser_reset(&st);
	}
}
