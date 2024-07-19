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

	params->flag_2 = 0;
	params->save_fd = -1;
	params->flag = 0;
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
					update_(st, params);
					if (!ft_strlen(st->cmd[0]))
					{
						printf("command not found\n");
						st = st->next;
						continue ;
					}
					// if (params->cmds > 1)
					// {
					// 	puts("here");
					if (!(params->cmds == 1 && check_builtins(st->cmd[0])))
						forking_piping(params, i);
					// }
					if ((!(params->pid) || (params->cmds == 1 && params->pid )) && checking_cmd(st, params))
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
					if (((!(params->pid)) || (params->cmds == 1 && params->pid )) && checking_cmd2(st, params))
					{
						tokens_reset(&token);
						parser_reset(&st);
						continue ;
					}
					if (!st->com_path)
					{
						if (!params->pid)
						{
							close (params->fds[0]);
							close (params->fds[1]);
							exit (1);
						}
						params->flag = 1;
						printf("%s :command not found\n", st->cmd[0]);
						// reset_pipe(stdin_copy, stdout_copy);
					}
					else
						excute_cmd(st, params);
					// else
   					// {
						if (params->pid != 0)
						{

							// int	status;
   						// wait(0);
							if (i == params->cmds - 1)
							{
								waitpid(params->pid, 0, 0);
								// close(fds[0]);
								// close(fds[1]);
							}
							// waitpid(pid, &status, 0);
							params->flag = 0; // this could cause a problem
							if (i != 0)
								close(params->save_fd);
   					   		if (i != params->cmds - 1)
   					  		{
   					       		close(params->fds[1]);
								params->save_fd = params->fds[0];
								params->flag_2 = 1;
   					   		}
						}
   					// }
					st = st->next;
					i++;
				}
				params->save_fd = -1;
				params->flag_2 = 0;
				i = 0;
				while (wait(0) != -1 || errno != ECHILD)
					;
			}
		}
		tokens_reset(&token);
		parser_reset(&st);
	}
}
