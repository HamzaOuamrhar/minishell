/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:02:07 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/06 15:31:18 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exiting(t_params *params, int status)
{
	close(params->fds[0]);
	close(params->fds[1]);
	exit (status);
}

void	closing_fds(t_params *params)
{
	int	status;

	close (params->fds[1]);
	if (params->save_fd != -1)
		close (params->save_fd);
	if (params->i == params->cmds - 1)
	{
		waitpid(params->pid, &status, 0);
		if (WIFEXITED(status))
			params->status = WEXITSTATUS(status);
		close(params->fds[0]);
		close(params->fds[1]);
	}
	params->flag = 0;
	if (params->i != params->cmds - 1)
	{
		params->save_fd = params->fds[0];
		params->flag_2 = 1;
	}
	else
		close (params->fds[0]);
}

void	executing(t_parse *st, t_params *params)
{
	int	status;

	status = 0;
	params->flag = 0;
	pipe(params->fds);
	params->pid = fork();
	if (fork_failure(params))
		return ;
	if (!params->pid)
	{
		signal_handle2();
		forking_piping(params);
		if (just_a_checker(st, params))
			status = 1;
		if (check_builtins(st->cmd[0]))
			status = checking_cmd(st, params);
		else
		{
			slash_path(st, params);
			checking_and_exec(st, params);
		}
		exiting(params, status);
	}
	closing_fds(params);
}

void	excute_cmds(t_parse *st, t_params *params)
{
	if (params->cmds == 1 && check_builtins(st->cmd[0]))
	{
		if (just_a_checker(st, params))
			params->status = 1;
		else
			params->status = checking_cmd(st, params);
		if (params->stdin_ != -1)
		{
			dup2(params->stdin_, 0);
			close (params->stdin_);
			close(st->in_fd);
		}
		if (params->stdout_ != -1)
		{
			dup2(params->stdout_, 1);
			close (params->stdout_);
			close(st->out_fd);
		}
	}
	else
		executing(st, params);
}
