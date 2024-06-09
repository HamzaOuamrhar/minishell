/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:04:19 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/06/09 14:02:03 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_syntax(char *s)
{
	int	i;

	i = 0;
	if (!((s[i] >= 'a' && s[i] <= 'z')
			|| (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_')))
		return (1);
	return (0);
}

// void	pwd_cmd(t_parse *st)
// {
// 	char	*pwd;

// 	pwd = get_pwd(st);
// 	printf("%s\n", pwd);
// 	free (pwd);
// }

void	pwd_cmd(t_params *params)
{
	char	*pwd;
	// DIR		*dir;s->env), "..");
	// 	printf("%s\n", pwd);
	// 	free (pwd);
	// 	return ;
	// }
	pwd = malloc (1024);

	// dir = opendir(get_key("PWD", params->env));
	// if (!dir)
	// {
	// 	// search_and_replace("PWD", "..", params->env);
	// 	pwd = ft_strjoin2(get_key("PWD", param
	if (!pwd)
		return ; // more protection
	if (!(getcwd(pwd, 1024)))
	{
		// printf("cd: error retrieving current directory: getcwd\n");
		printf("%s\n", get_key("PWD", params->env));
	}
	else
		printf("%s\n", pwd);
	free (pwd);
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
			tmp->next = tmp->next->next;
			free (tmp2->key);
			free (tmp2->value);
			free (tmp2);
			return ;
		}
		tmp = tmp->next;
	}
}

void	unset_cmd(t_parse *st, t_params *params)
{
	int	i;

	i = 1;
	while (st->cmd[i])
	{
		if (check_syntax(st->cmd[i]))
			printf("Shellantics: export: `%s': not a valid identifier\n", st->cmd[i]);
		else
		{ 
			unset_cmd1(&(params->env), st->cmd[i]);
			unset_cmd1(&(params->sorted_env), st->cmd[i]);
		}
		i++;
	}
	free_update(NULL, params);
}

int	checking_cmd3(t_parse *st, t_params *params)
{
	if (!ft_strcmp(st->cmd[0], "pwd")) // enter with deleted directory
	{
		pwd_cmd(params);
		return (1);
	}
	if (!ft_strcmp(st->cmd[0], "unset")) // enter with deleted directory
	{
		unset_cmd(st, params);
		return (1);
	}
	if (ft_strcmp(st->cmd[0], "cd") == 0)
	{
		change_directory(st, params);
		return (1);
	}
	return (0);
}
