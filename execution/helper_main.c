#include "../minishell.h"

int	just_a_checker(t_parse *st, t_params *params)
{
	if (st->files || st->in_dup) //add redidrection to the pipes
	{
		if (in_out_dup(st, params))
			return (1);
	}
	if (!st || !st->cmd[0] || (!st->files && !st->cmd))
		return (1);
	return (0);
}

void	excute_builtins(t_parse *st, t_params *params)
{
	checking_cmd(st, params);
}

void	executing(t_parse *st, t_params *params, t_token *token)
{
	(void)token;
	forking_checker(st, params);
	if (!params->pid)
	{
		just_a_checker(st, params);
		if (check_builtins(st->cmd[0]))
			checking_cmd(st, params);
		else
		{
			if (!st->com_path || !ft_strlen(st->cmd[0])) //check the "." and ".."
			{
				if (!params->pid)
				{
					close (params->fds[0]);
					close (params->fds[1]);
					// exit (0);
				}
				params->flag = 1;
				_g_signal = 127;
				printf("shellantics: %s :command not found\n", st->cmd[0]); //this is just a function
			}
			else
				excute_cmd(st, params);
		}
		exit (0);
	}
	if (params->i == params->cmds - 1)
	{
		waitpid(params->pid, 0, 0);
		return ;
		close(params->fds[0]);
		close(params->fds[1]);
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

void	excute_cmds(t_parse *st, t_params *params, t_token *token)
{
	if (check_in_files(st, params))
		return ;
	if (params->cmds == 1 && check_builtins(st->cmd[0]))
		excute_builtins(st, params);
	else
	{
		puts("here");
		executing(st, params, token);
		// other_cmds(st, params, token);
	}
}