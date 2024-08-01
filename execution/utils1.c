/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:23:49 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/01 18:30:39 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_acc_path(char **paths, char *com)
{
	int		i;
	char	*r;
	char	*rr;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		r = ft_strjoin2(paths[i], "/");
		rr = ft_strjoin2(r, com);
		free(r);
		if (access(rr, F_OK | X_OK) == 0)
			return (rr);
		i++;
		free(rr);
	}
	return (NULL);
}

void	slash_path(t_parse *st, t_params *params)
{
	(void)params;
	if (!st->cmd || !st->cmd[0]
		|| !(ft_strcmp(".", st->cmd[0])) || !(ft_strcmp("..", st->cmd[0])))
		st->com_path = NULL;
	// else if (access(st->cmd[0], X_OK))
	// 	st->com_path = get_acc_path(params->paths_array, st->cmd[0]);
	else
		st->com_path = ft_copy(st->cmd[0]);
}

int	pwd_cmd(t_params *params)
{
	char	*pwd;
	char	*tmp;

	pwd = malloc (1024);
	if (!pwd)
	{
		perror("malloc");
		return (1);
	}
	if (!(getcwd(pwd, 1024)))
	{
		tmp = get_key("PWD", params->env);
		if (!tmp)
		{
			write(2, "we can't get the working directory\n", 35);
			return (1);
		}
		else
			printf("%s\n", get_key("PWD", params->env));
	}
	else
		printf("%s\n", pwd);
	free (pwd);
	return (0);
}

int	checking_cmd3(t_parse *st, t_params *params)
{
	if (!ft_strcmp(st->cmd[0], "pwd"))
		return (pwd_cmd(params));
	if (!ft_strcmp(st->cmd[0], "unset"))
		return (unset_cmd(st, params));
	if (ft_strcmp(st->cmd[0], "cd") == 0)
		return (change_directory(st, params));
	if (ft_strcmp(st->cmd[0], "echo") == 0)
		return (echo_cmd(st));
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
			else if (tmp->next)
				tmp->next = NULL;
			else
				tmp = NULL;
			free (tmp2->key);
			free (tmp2->value);
			free (tmp2);
			return ;
		}
		tmp = tmp->next;
	}
}
