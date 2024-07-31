/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:43:35 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/07/31 21:40:29 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	no_permissions(t_params *params)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	tmp = ft_copy(get_key("PWD", params->env));
	i = ft_strlen(tmp);
	i--;
	while (tmp[i] && tmp[i] != '/')
		i--;
	tmp2 = ft_substr(tmp, 0, i);
	if (access(tmp2, X_OK) == -1)
	{
		printf("shellantics: cd: ..: Permission denied\n");
		free (tmp2);
		free (tmp);
		return ;
	}
	if (chdir(tmp2) == -1)
	{
		printf("chdir error\n");
		exit (1);
	}
	search_and_replace("OLDPWD", ft_copy(get_key("PWD", params->env)),
		&(params->env), 1);
	search_and_replace("PWD", tmp2, &(params->env), 1);
}

void	print_error(char *cmd, char *s, char *folder)
{
	write (2, "shellantics: ", 13);
	if (cmd)
		write (2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	if (folder)
		write (2, folder, ft_strlen(folder));
	write (2, s, ft_strlen(s));
}

int	unset_cmd(t_parse *st, t_params *params)
{
	int	i;

	i = 1;
	while (st->cmd[i])
	{
		if (check_syntax(st->cmd[i]))
		{
			print_error("env", ": not a valid identifier\n", st->cmd[i]);
			_g_signal = 1;
		}
		else if (!ft_strcmp("_", st->cmd[i]))
			_g_signal = 0;
		else
		{
			unset_cmd1(&(params->env), st->cmd[i]);
			unset_cmd1(&(params->sorted_env), st->cmd[i]);
			_g_signal = 0;
		}
		i++;
	}
	free_update(NULL, params);
	return (_g_signal);
}
