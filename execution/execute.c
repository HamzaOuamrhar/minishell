/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:02:07 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/03 15:57:50 by iez-zagh         ###   ########.fr       */
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
			g_status = WEXITSTATUS(status);
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
		exiting(params, status);
	}
	closing_fds(params);
}

void	excute_cmds(t_parse *st, t_params *params)
{
	if (check_in_files(st, params))
	{
		g_status = 1;
		return ;
	}
	if (params->cmds == 1 && check_builtins(st->cmd[0]))
		g_status = checking_cmd(st, params);
	else
		executing(st, params);
}

void	cloing_fds(t_params *params)
{
	int	status;

	close (params->fds[1]);
	if (params->save_fd != -1)
		close (params->save_fd);
	if (params->i == params->cmds - 1)
	{
		waitpid(params->pid, &status, 0);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		close(params->fds[0]);
		close(params->fds[1]);
	}
	params->flag = 0;
	if (params->i != params->cmds - 1)
	{
		params->save_fd = params->fds[0];
		params->flag_2 = 1;
	}
}
