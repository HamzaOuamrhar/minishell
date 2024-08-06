/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:40:06 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/06 13:38:08 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_shell_itoa(int n)
{
	char	*res;
	int		counter;
	int		n1;

	n1 = n;
	counter = 0;
	while (n1)
	{
		counter++;
		n1 = n1 / 10;
	}
	res = malloc (counter + 1);
	if (!res)
		return (NULL);
	res[counter] = '\0';
	counter--;
	while (counter >= 0)
	{
		res[counter] = (n % 10) + '0';
		n = n / 10;
		counter--;
	}
	return (res);
}

void	update_shlvl(t_params *params)
{
	int			n;
	char		*lvl;

	rl_catch_signals = 0;
	n = ft_shell_atoi(get_key("SHLVL", params->env));
	if (n == -1)
		return (search_and_replace("SHLVL", ft_copy(params, "1"),
				&(params->sorted_env), 1),
			search_and_replace("SHLVL", ft_copy(params, "1"),
				&(params->env), 1));
	if (n == -2)
		lvl = ft_copy(params, "0");
	else if (++n == 999)
	{
		search_and_replace("SHLVL", ft_copy(params, ""),
			&(params->sorted_env), 1);
		search_and_replace("SHLVL", ft_copy(params, ""), &(params->env), 1);
	}
	if (n != -1 && n != -2)
		lvl = ft_shell_itoa(n);
	if (!lvl)
		malloc_error(params);
	search_and_replace("SHLVL", lvl, &(params->sorted_env), 1);
	search_and_replace("SHLVL", ft_copy(params, lvl), &(params->env), 1);
}

void	update(t_params *params)
{
	char	*_;

	_ = get_acc_path(params->paths_array, "env");
	search_and_replace("_", _, &(params->env), 1);
	search_and_replace("_", _, &(params->sorted_env), 1);
	update_shlvl(params);
}
