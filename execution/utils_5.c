/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:04:19 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/07/31 18:01:52 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax(char *s)
{
	int	i;
//_ in beging   digits in middle no digits in beg
	i = 0;
	if (!((s[i] >= 'a' && s[i] <= 'z') //complete the checks  untill the end
			|| (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_')))
		return (1);
	return (0);
}

void	unset_cmd1(t_env **env, char *s)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = *env;
	while (tmp->next)
	{
		if (!(ft_strcmp(tmp->next->key, s)))
		{
			tmp2 = tmp->next;
			if (tmp->next->next)
				tmp->next = tmp->next->next;
			else
				tmp->next  = NULL;
			free (tmp2->key);
			free (tmp2->value);
			free (tmp2);
			return ;
		}
		tmp = tmp->next;
	}
}

int	exec_echo(int i, t_parse *st)
{
	int	j;

	j = i;
	while (st->cmd[i])
	{
		if (!(write(1, st->cmd[i], ft_strlen(st->cmd[i]))))
		{
			perror("write");
			return (1);
		}
		i++;
		if (st->cmd[i])
			write(1, " ", 1);
	}
	if (j == 1)
	{
		if (!(write(1, "\n", 1)))
		{
			perror("write");
			return (1);
		}
		
	}
	return (0);
}

int	echo_cmd(t_parse *st)
{
	int	i;
	int	j;

	i = 1;
	while (st->cmd[i])
	{
		if (st->cmd[i][0] != '-')
			return (exec_echo(i, st));
		j = 1;
		while (st->cmd[i][j])
		{
			if (st->cmd[i][j] != 'n')
				return (exec_echo(i, st));
			j++;
		}
		i++;
	}
	return (0);
}

int	checking_cmd3(t_parse *st, t_params *params)
{
	if (!ft_strcmp(st->cmd[0], "pwd")) // enter with deleted directory
		return (pwd_cmd(params));
	if (!ft_strcmp(st->cmd[0], "unset")) // enter with deleted directory
		return (unset_cmd(st, params));
	if (ft_strcmp(st->cmd[0], "cd") == 0)
		return (change_directory(st, params));
	if (ft_strcmp(st->cmd[0], "echo") == 0)
		return (echo_cmd(st));
	return (0);
}
