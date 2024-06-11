/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:52:27 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/06/11 18:33:12 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	excute_cmd(t_parse *st, t_params *params)
{
	int	pid;

	// ft_free(params->env2);
	// params->env2 = list2array(params->env, params);
	pid = fork();
	if (pid == 0)
		execve(st->com_path, st->cmd, params->env2); //protection
	wait(0);
}

void change_directory(t_parse *st, t_params *params)
{
	char	*home;

	if (count_args(st->cmd) == 1)
	{
		home = get_key("HOME", params->env);
		if (!home)
		{
			printf("Shellantics: cd: HOME not set\n");
			return ;
		}
		change_dir(st, params, home);
		return ;
	}
	change_dir(st, params, st->cmd[1]);
}

void	excute_file(t_parse *st, t_params *params)
{
	int		pid;
	char	*tmp;

	tmp = ft_substr(st->cmd[0] ,2 , ft_strlen(st->cmd[0]));
	if (access(tmp, X_OK) == -1)
	{
		printf("%s: Permission denied\n", st->cmd[0]);
		free (tmp);
		params->status = 126;
		return ;
	}
	pid = fork();
	free (tmp);
	if (pid == 0)
		if (execve(st->cmd[0], st->cmd, params->env2) == -1)
		{
			params->status = 127;
			printf("Shellantics: %s: No such file or directory\n", st->cmd[0]);
		}
	wait (0);
}

void	terminate_shell(t_parse *st, t_params *params)
{
	int	args_n;

	args_n = count_args(st->cmd);
	if (args_n == 1 || args_n == 2)
		ft_exit(st, args_n, params);
	if (!(numbered_arg(st->cmd[1])) && (count_args(st->cmd)) > 2)
	{
		printf("exit\nShellantics: exit: too many arguments\n");
		return ;
	}
	if ((numbered_arg(st->cmd[1])))
	{
		printf("exit\nShellantics: exit: %s: numeric argument required\n", st->cmd[1]);
		// freeing(st, params);
		exit (255);
	}
}
