/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 20:52:27 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/07/31 13:37:15 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	excute_cmd(t_parse *st, t_params *params)
{
	// ////imad"exection");
	if (params->pid == 0)
		execve(st->com_path, st->cmd, params->env2);
}

int change_directory(t_parse *st, t_params *params)
{
	char	*home;

	if (count_args(st->cmd) == 1)
	{
		home = get_key("HOME", params->env);
		if (!home)
			return (print_error("cd", ": HOME not set\n", NULL), 1);
		change_dir(st, params, home);
		return (0);
	}
	return (change_dir(st, params, st->cmd[1]));
}

int	terminate_shell(t_parse *st, t_params *params)
{
	int	args_n;

	args_n = count_args(st->cmd);
	if (args_n == 1 || args_n == 2)
		ft_exit(st, args_n, params);
	if (!(numbered_arg(st->cmd[1])) && (count_args(st->cmd)) > 2)
	{
		write(2, "exit\n", 5);
		print_error("exit",": too many arguments\n", NULL);
		return (1);//its one 
	}
	if ((numbered_arg(st->cmd[1])))
	{
		write(2, "exit\n", 5);
		print_error("exit", ": numeric argument required\n", NULL);
		// freeing(st, params);
		exit (255);
	}
	return (0);
}
