/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:43:44 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/04 11:29:02 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	trying_with_pwd(t_params *params)
{
	char	*pwd;

	(void)params;
	pwd = malloc(1024 * (sizeof(char)));
	if (!pwd)
	{
		perror("malloc");
		return (1);
	}
	getcwd(pwd, 1024);
	if (!pwd)
	{
		write(2, "some thing went wrong here\n", 28);
		g_status = 1;
		free (pwd);
		return (1);
	}
	else
	{
		search_and_replace(ft_copy("PWD"), pwd, &(params->env), 0);
		search_and_replace(ft_copy("PWD"), ft_copy(pwd), &(params->sorted_env), 0);
	}
	return (0);
}

void	change_pwd2(char *tmp2, t_params *params, char *tmp)
{
	if (access(tmp2, F_OK) != -1)
	{
		search_and_replace(ft_copy("PWD"), ft_copy(tmp2), &(params->env), 0);
		search_and_replace(ft_copy("PWD"), ft_copy(tmp2), &(params->sorted_env), 0);
	}
	else
	{
		search_and_replace(ft_copy("PWD"),
			ft_strjoin2(tmp, "/.."), &(params->env), 0);
		search_and_replace(ft_copy("PWD"),
			ft_strjoin2(tmp, "/.."), &(params->sorted_env), 0);
	}
}

int	check_deleted(t_params *params, char *tmp2)
{
	struct stat	the_path;
	char		*tmp;

	tmp = get_key("PWD", params->env);
	if (!tmp)
		return (0);
	stat(tmp, &the_path);
	if (!S_ISDIR(the_path.st_mode))
	{
		chdir("..");
		write(2, "cd: error retrieving current ", 29);
		write(2, "directory: getcwd\n", 18);
		search_and_replace("OLDPWD",
			ft_copy(get_key("PWD", params->env)), &(params->env), 1);
		search_and_replace("OLDPWD",
			ft_copy(get_key("PWD", params->env)), &(params->sorted_env), 1);
		change_pwd2(tmp2, params, tmp);
		return (1);
	}
	return (0);
}

char	*ft_spliter(char *s, int j)
{
	int		i;
	char	*pwd;

	(void)j;
	if (!s)
		return (NULL);
	pwd = malloc(1024);
	if (!pwd)
	{
		perror("malloc");
		return (NULL);
	}
	getcwd(pwd, 1024);
	i = 0;
	i = ft_strlen(pwd) - 1;
	while (pwd[i] && (pwd[i] != '/'))
		i--;
	char *pwd2 = ft_substr(pwd, 0, i);
	free (pwd);
	return (pwd2);
}

void	change_pwd(t_params *params, char *tmp, int *i)
{
	change_pwd_value(params);
	free (tmp);
	*i = 0;
}

int	 change_dir(t_parse *st, t_params *params, char *s)
{
	struct stat	the_path;
	char		*tmp = NULL;
	static int	i = 0;

	stat(s, &the_path);
	tmp = ft_spliter(get_key("PWD", params->env), i);
	if (!tmp)
	{
		if (trying_with_pwd(params))
			return (1);
		return (change_dir(st, params, s));
	}
	if (access(tmp, F_OK) == -1 && !(ft_strcmp("..", st->cmd[1])))
		return (free(tmp), check_deleted(params, tmp), i++, 1);
	else if (S_ISDIR(the_path.st_mode) && access(s, X_OK) == -1)
		return (free(tmp), print_error("cd", ": Permission denied\n", s), 1);
	else if (!S_ISDIR(the_path.st_mode) && access(s, F_OK) != -1)
		return (free(tmp), print_error("cd", ": not a directory\n", s), 1);
	else if (chdir(s) == -1)
		return (free(tmp), print_error("cd",
				": no such file or directory\n", s), 1);
	else
		change_pwd(params, tmp, &i);
	return (0);
}
