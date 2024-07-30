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

int	check_in_files(t_parse *st, t_params *params)
{
	if (check_perms(st, params))
		return (1);
	return (0);
}

int	just_a_checker(t_parse *st, t_params *params)
{
	// puts("gets to inpu");
	if (st->files || st->in_fd || st->in_dup) //add redidrection to the pipes
	{
		if (in_out_dup(st, params))
			return (1);
	}
	if (!st || !st->cmd[0] || (!st->files && !st->cmd))
		return (1);
	return (0);
}

void	wait_prompt1(t_params *params)
{
	t_token		*token;
	t_parse		*st;

	initialiaze_vars(params, &token, 1);
	st = NULL;
	token = NULL;
	while (1)
	{
		signal_handle();
		_g_signal = 0;
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
				if (_g_signal)
				{
					tokens_reset(&token);
					parser_reset(&st);
					continue;
				}
				params->cmds = lstsize(st);
				// print(st);
				params->i = 0;
				while (st)
				{
					// if (st && st->next)
					puts("its first");
					update_(st, params);
					// if (check_in_files(st, params))
					// {
					// 	// st = st->next;
					// 	tokens_reset(&token);
					// 	parser_reset(&st);
					// 	// st = st->next;
					// 	// if (st->next)
					// 	// 	puts("not null");
					// 	// printf("[%s]\n", st->in_dup);//sgv here
					// 	continue ;
					// }
					excute_cmds(st, params); //here the super hero
					forking_checker(st, params);
					////imad"first");
					if (check_in_files(st, params) || ((!params->pid || (params->cmds == 1 && params->pid )) && just_a_checker(st, params)))
					{
						// forking_piping()
						puts("here");
						////imad"in checker");
						tokens_reset(&token);
						// parser_reset(&st);
						st = st ->next;
						if (!params->pid)
							exit (0);
						continue ;
					}
					////imad"hello form main");
					if ((!(params->pid) || (params->cmds == 1 && params->pid )) && checking_cmd(st, params))
					{
						// puts("builtins");
						tokens_reset(&token);
						st = st->next;
						// parser_reset(&st);
						if (!params->pid)
							exit (0);
						continue ;
					}
					if (!params->path && params->pid)
					{
						while (st->next)
							st = st->next;
						printf("Shellantics: %s: No such file or directory\n", st->cmd[0]);
						tokens_reset(&token);
						parser_reset(&st);
						if (!params->pid)
							exit (0);
						continue ;
					}
					if (((!(params->pid)) || (params->cmds == 1 && params->pid )) && checking_cmd2(st, params))
					{
						tokens_reset(&token);
						parser_reset(&st);
						if (!params->pid)
							exit (0);
						continue ;
					}
					if (!st->com_path || !ft_strlen(st->cmd[0])) //check the "." and ".."
					{
						if (!params->pid)
						{
							close (params->fds[0]);
							close (params->fds[1]);
							exit (0);
						}
						params->flag = 1;
						_g_signal = 127;
						// puts("here");
						printf("shellantics: %s :command not here found\n", st->cmd[0]); //this is just a function
					}
					else
						excute_cmd(st, params);
					if (params->pid != 0)
					{
						if (params->i == params->cmds - 1)
						{
							waitpid(params->pid, 0, 0);
							// close(fds[0]);
							// close(fds[1]);
						}
						params->flag = 0; // this could cause a problem
						if (params->i != 0)
							close(params->save_fd);
						if (params->i != params->cmds - 1)
						{
							close(params->fds[1]);
							params->save_fd = params->fds[0];
							params->flag_2 = 1;
						}
					}
					st = st->next;
					params->i++;
				}
				while (waitpid(-1, NULL, 0) > 0 || errno != ECHILD)
					;
				initialiaze_vars(params, &token, 0);
			}
		}
		tokens_reset(&token);
		parser_reset(&st);
	}
}