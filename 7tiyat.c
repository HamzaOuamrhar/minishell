void	other_cmds(t_parse *st, t_params *params, t_token *token)//problem in herdoc ne9a
{
	(void)token;
	if (just_a_checker(st, params))
		return ;
	forking_checker(st, params);
	if (check_builtins(st->cmd[0]))
	{
	puts("here");
		// printf("pid %d tttt %d\n", params->pid, (!params->pid && check_builtins(st->cmd[0])));
		// puts("gets here");
		// printf ("%s]]\n", st->cmd[0]);
		// tokens_reset(&token);
		// parser_reset(&st);
		if (!params->pid)
		{
			checking_cmd(st, params);
			// if (!params->pid)
				exit(0);
		}
		// if (!params->pid)
			// exit(0);
		// return ;
	}
	else
	{
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
			printf("shellantics: %s :command not found\n", st->cmd[0]); //this is just a function
		}
		else
			excute_cmd(st, params);
	}
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
}