/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:05:38 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/07/06 14:01:28 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checking_cmd(t_parse *st, t_params *params)
{
	params->status = 0;
	// print(st);
	if (!st || !st->cmd[0] || (!st->files && !st->cmd))
		return (1);
	if (st->files || st->in_fd)
	{
		if (in_out_dup(st, params))
			return (1);
	}
	if (!(ft_strcmp(st->cmd[0], "exit")))
	{
		terminate_shell(st, params);
		return (1);
	}
	if (!ft_strcmp(st->cmd[0], "export"))
	{
		export_cmd1(st, params);
		return (1);
	}
	if (st->cmd[0][0] == '.' && st->cmd[0][1] == '/')
	{
		excute_file(st, params); 
		return (1);
	}
	if (checking_cmd3(st, params))
		return (1);
	return (0);
}

int	env_cmd(t_parse	*st, t_params *params)
{
	t_env	*tmp;

	if (count_args(st->cmd) > 1)
	{
		printf ("minishell: env: Too many arguments.\n");
		return (1);
	}
	tmp = params->env;
	while (tmp)
	{
		if (!tmp->value)
			printf("%s\n", tmp->key);
		else
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (1);
}

char	**list2array(t_env *env, t_params *params)
{
	char	**env2;
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = params->env;
	env2 = malloc (sizeof(char *) * (lstcounter(env) + 1));
	// if (!env2)
	// 	error(st, 2, params); // chechk another protection
	while (tmp)
	{
		env2[i++] = ft_strjoin_env(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	env2[i] = NULL;
	return (env2);
}

int	lstcounter(t_env	*env)
{
	int	counter;

	counter = 0;
	while (env)
	{
		env = env->next;
		counter++;
	}
	return (counter);
}
