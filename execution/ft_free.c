/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:19:56 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/01 17:19:57 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free (env);
		env = tmp;
	}
}

void	freeing(t_parse *st, t_params *params)
{
	free(params->path);
	free_list(params->env);
	free_list(params->sorted_env);
	if (st->cmd)
		ft_free(st->cmd);
	if (params->paths_array)
		ft_free(params->paths_array);
	ft_free(params->env2);
	free (st);
}

void	ft_free(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		free (s[i++]);
	free (s);
}

void	change_pwd_value(t_params *params)
{
	search_and_replace("OLDPWD",
		ft_copy(get_key("PWD", params->env)), &(params->env), 1);
	search_and_replace("PWD", get_pwd(params), &(params->env), 1);
}
