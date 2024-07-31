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
	_g_signal = checking_cmd(st, params);
}

void	no_path(t_parse *st, t_params *params)
{
	if (!params->pid)
	{
		close (params->fds[0]);
		close (params->fds[1]);
	}
	params->flag = 1;
	_g_signal = 127;
	print_error(st->cmd[0], ": No such file or directory\n", NULL);
	exit (127);
}

void	checking_and_exec(t_parse *st, t_params *params)
{
	if (!(get_key("PATH", params->env)))
		no_path(st, params);
	else if (!st->com_path || !ft_strlen(st->cmd[0])) //check the "." and ".."
	{
		if (!params->pid)
		{
			close (params->fds[0]);
			close (params->fds[1]);
		}
		params->flag = 1;
		_g_signal = 127;
		print_error(st->cmd[0], ": command not found\n", NULL);
		exit (127);
	}
	else
		excute_cmd(st, params);	
}

void	executing(t_parse *st, t_params *params, t_token *token)
{
	int	status;

	(void)token;
	status = 0;
	params->flag = 0;
	pipe(params->fds);
	params->pid = fork();
	if (!params->pid)
	{
		forking_piping(params);
		if (check_builtins(st->cmd[0]))
			status = checking_cmd(st, params);
		else
		{
			if (just_a_checker(st, params))
				status = 0;
			else
			{
				slash_path(st, params);
				checking_and_exec(st, params);
			}
		}
		exit (status);
	}
	close (params->fds[1]);
	close (params->save_fd);
	if (params->i == params->cmds - 1)
	{
		waitpid(params->pid, &status, 0);
		if (WIFEXITED(status))
			_g_signal = WEXITSTATUS(status);
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
	{
		_g_signal = 1;
		return ;
	}
	if (params->cmds == 1 && check_builtins(st->cmd[0]))
		excute_builtins(st, params);
	else
		executing(st, params, token);
}
