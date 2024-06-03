/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:04:19 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/06/03 17:12:33 by houamrha         ###   ########.fr       */
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

void	pwd_cmd(t_parse *st)
{
	char	*pwd;
	// DIR		*dir;

	// dir = opendir(get_key("PWD", st->env));
	// if (!dir)
	// {
	// 	// search_and_replace("PWD", "..", st->env);
	// 	pwd = ft_strjoin(get_key("PWD", st->env), "..");
	// 	printf("%s\n", pwd);
	// 	free (pwd);
	// 	return ;
	// }
	pwd = malloc (1024);
	if (!pwd)
		return ; // more protection
	if (!(getcwd(pwd, 1024)))
	{
		// printf("cd: error retrieving current directory: getcwd\n");
		printf("%s\n", get_key("PWD", st->env));

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

void	unset_cmd(t_parse *st)
{
	int	i;

	i = 1;
	while (st->cmd[i])
	{
		unset_cmd1(&(st->env), st->cmd[i]);
		unset_cmd1(&(st->sorted_env), st->cmd[i++]);
	}
	free_update(NULL, st);
}

int	checking_cmd3(t_parse *st)
{
	if (!ft_strcmp(st->cmd[0], "pwd")) // enter with deleted directory
	{
		pwd_cmd(st);
		ft_free2(st);
		return (1);
	}
	if (!ft_strcmp(st->cmd[0], "unset")) // enter with deleted directory
	{
		unset_cmd(st);
		ft_free2(st);
		return (1);
	}
	if (ft_strncmp(st->cmd[0], "cd", 2) == 0)
	{
		change_directory(st);
		ft_free2(st);
		return (1);
	}
	return (0);
}
