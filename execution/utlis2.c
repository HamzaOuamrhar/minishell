/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:05:38 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/01 09:25:59 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	checking_cmd(t_parse *st, t_params *params)
{
	if (!(ft_strcmp(st->cmd[0], "exit")))
		return (terminate_shell(st, params));
	if (!ft_strcmp(st->cmd[0], "export"))
		return (export_cmd1(st, params));
	if (!ft_strcmp("env", st->cmd[0]))
		return (env_cmd(st, params));
	return (checking_cmd3(st, params));
	return (0);
}

int	env_cmd(t_parse	*st, t_params *params)
{
	t_env	*tmp;

	if (!get_key("PATH", params->env))
		return (print_error("env", "No such file or directory\n", NULL), 127);
	search_and_replace("_", get_acc_path(params->paths_array, "env"), &(params->env), 1);
	if (count_args(st->cmd) > 1)
	{
		print_error("env", ": Too many arguments\n", NULL);
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
	search_and_replace("_", ft_copy("env"), &(params->env), 1);
	return (0);
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

int	lstsize(t_parse	*env)
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
