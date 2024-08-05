/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 13:23:49 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/05 11:49:08 by iez-zagh         ###   ########.fr       */
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
	char	*tmp;

	tmp = NULL;
	if (st->cmd[0][0] == '.' && st->cmd[0][1] == '/')
		if (minishell(st))
			return ;
	if (!st->cmd || !st->cmd[0]
		|| !(ft_strcmp(".", st->cmd[0])) || !(ft_strcmp("..", st->cmd[0])))
	{
		st->com_path = NULL;
		return ;
	}
	st->com_path = get_acc_path(params->paths_array, st->cmd[0]);
	if (st->com_path)
		return ;
	if (ft_strchr(st->cmd[0], '/'))
		tmp = ft_slashs(st);
	if (tmp)
		st->com_path = get_acc_path(params->paths_array, tmp);
	if (access(st->cmd[0], X_OK) && st->com_path)
		st->com_path = ft_copy(st->cmd[0]);
	free (tmp);
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
			free (pwd);
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

void	ft_unseting(t_env *tmp, t_env **env, t_env *tmp2)
{
	tmp2 = tmp;
	if (tmp->next)
		*(env) = tmp->next;
	else
		tmp->next = NULL;
}

void	unset_cmd1(t_env **env, char *s)
{
	t_env		*tmp;
	t_env		*tmp2;

	tmp = *env;
	tmp2 = NULL;
	while (tmp)
	{
		if (tmp->next)
		{
			if (!(ft_strcmp(tmp->next->key, s)))
			{
				tmp2 = tmp->next;
				tmp->next = tmp->next->next;
				break ;
			}
		}
		if (!(ft_strcmp(tmp->key, s)))
		{
			ft_unseting(tmp, env, tmp2);
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp2)
		return (free(tmp2->key), free(tmp2->value), free(tmp2));
}
