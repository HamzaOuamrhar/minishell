/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:19:56 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/06 13:34:56 by iez-zagh         ###   ########.fr       */
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

void	freeing(t_params *params)
{
	free(params->path);
	free_list(params->env);
	if (params->paths_array)
		ft_free(params->paths_array);
	ft_free(params->env2);
	ft_malloc(0, 3);
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
	char	*tmp;

	tmp = get_key("PWD", params->env);
	if (tmp)
	{
		search_and_replace(ft_copy(params, "OLDPWD"), ft_copy(params, tmp),
			&(params->env), 0);
		search_and_replace(ft_copy(params, "OLDPWD"), ft_copy(params, tmp),
			&(params->sorted_env), 0);
	}
	else
	{
		search_and_replace(ft_copy(params, "OLDPWD"), "",
			&(params->env), 0);
		search_and_replace(ft_copy(params, "OLDPWD"), "",
			&(params->sorted_env), 0);
	}
	search_and_replace(ft_copy(params, "PWD"), get_pwd(params),
		&(params->sorted_env), 0);
	search_and_replace(ft_copy(params, "PWD"),
		get_pwd(params), &(params->env), 0);
}
