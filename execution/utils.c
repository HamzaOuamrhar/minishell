/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:52:27 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/06/03 17:12:33 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	excute_cmd(t_parse *st)
{
	int	pid;

	ft_free(st->env2);
	st->env2 = list2array(st->env, st);
	pid = fork();
	if (pid == 0)
		execve(st->com_path, st->cmd, st->env2); //protection
	wait(0);
	return ;
}

void change_directory(t_parse *st)
{
	char	*home;

	if (count_args(st->cmd) == 1)
	{
		home = get_key("HOME", st->env);
		if (!home)
		{
			printf("Shellantics: cd: HOME not set\n");
			// ft_free(st->cmd);
			return ;
		}
		change_dir(st, home);
		return ;
	}
	change_dir(st, st->cmd[1]);
}

void	excute_file(t_parse *st)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		if (execve(st->cmd[0], st->cmd, st->env2) == -1)
			printf("Shellantics: %s: No such file or directory\n", st->cmd[0]);
	wait (0);
}

void	terminate_shell(t_parse *st)
{
	int	args_n;

	args_n = count_args(st->cmd);
	if (args_n == 1 || args_n == 2)
		ft_exit(st, args_n);
	if (!(numbered_arg(st->cmd[1])) && (count_args(st->cmd)) > 2)
	{
		printf("exit\nShellantics: exit: too many arguments\n");
		return ;
	}
	if ((numbered_arg(st->cmd[1])))
	{
		printf("exit\nShellantics: exit: %s: numeric argument required\n", st->cmd[1]);
		freeing(st);
		exit (255);
	}
}
