#include "../minishell.h"

void	parser_reset(t_parse **st)
{
	while (*st)
	{
		if ((*st)->in_fd)
			close((*st)->in_fd);
		(*st) = (*st)->next;
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
	bool		pipes;
	// int			i;

	token = NULL;
	// i = 0;
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
				params->cmds = lstsize(st);
				while (st)
				{
					if (lstsize(st) > 1)
					{
						// if
						// 
						// else
						// {
							// dup2(fds[1], STDOUT_FILENO);
						// 	dup2(fds[0], STDIN_FILENO);
						// }
					}
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
					{
						// puts("here");
						excute_cmd(st, params);
					}
					st = st->next;
					// i++;
				}
				// close (fds[1]);
				// close (fds[0]);
				pipes = true;
			}
		}
		tokens_reset(&token);
		parser_reset(&st);
	}
}

// void	handle_pipes(t_parse *st, t_params *params)
// {
// 	int	fds[2];

// 	pipe(fds);
// 	while ( )
// }