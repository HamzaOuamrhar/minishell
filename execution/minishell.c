/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:50:33 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/01 17:20:59 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char *argv[], char *env[])
{
	int			i;
	t_params	params;

	(void)argc;
	(void)argv;
	i = 0;
	if (!isatty(fileno(stdin)))
		return (printf("can't reach the tty standart input\n"), 1);
	if (!env || !env[0])
		empty_env(&params);
	else
		params.env3 = copy_env(env);
	params.env = set_env(params.env3, i);
	params.path = ft_copy(get_key("PATH", params.env));
	params.paths_array = ft_split(params.path, ':');
	params.sorted_env = set_env(params.env3, i);
	sort_env(params.sorted_env);
	ft_free(params.env3);
	update(&params);
	params.env2 = list2array(params.env, &params);
	wait_prompt1(&params);
}

void	ft_join(char **res, t_params *params)
{
	char	*res1;
	char	*res2;

	res1 = get_key(res[0], params->env);
	if (!res1)
		return ;
	res2 = ft_strjoin2(res1, res[1]);
	free (res[1]);
	res[1] = res2;
}

t_env	*before_last_node(t_env *env)
{
	while (env->next->next)
		env = env->next;
	return (env);
}
