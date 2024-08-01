/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:22:17 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/01 17:12:39 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_swap(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	sort_env(t_env *env)
{
	t_env	*tmp;
	int		sorted;

	if (env == NULL)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		tmp = env;
		while (tmp->next)
		{
			if (ft_strcmp(tmp->key, tmp->next->key) > 0)
			{
				ft_swap(tmp, tmp->next);
				sorted = 0;
			}
			tmp = tmp->next;
		}
	}
}

void	just_export(t_params *params)
{
	t_env	*tmp;

	tmp = params->sorted_env;
	while (tmp)
	{
		if (!(ft_strcmp("_", tmp->key)))
		{
			tmp = tmp->next;
			continue ;
		}
		if (!tmp->value)
			printf("declare -x %s\n", tmp->key);
		else
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	exporting(t_parse *st, t_params *params, char **res, int i)
{
	export_cmd(res, st->cmd[i], params);
	g_status = 0;
}

int	export_cmd1(t_parse *st, t_params *params)
{
	int		i;
	char	**res;

	res = NULL;
	if (count_args(st->cmd) == 1)
		return (just_export(params), 0);
	i = 1;
	while (st->cmd[i])
	{
		check_join(&(st->cmd[i]), st, params);
		res = export_checker(st->cmd[i]);
		if (!res || !res[0])
			return (perror("malloc"), 1);
		if (check_syntax(res[0]))
		{
			print_error("export", ": not a valid identifier\n", st->cmd[i]);
			g_status = 1;
		}
		else
			exporting(st, params, res, i);
		i++;
	}
	return (g_status);
}
