#include "../minishell.h"

int	pwd_cmd(t_params *params)
{
	char	*pwd;
	char	*tmp;

	pwd = malloc (1024);
	if (!pwd)
	{
		perror("malloc");
		return (1);
	}
	if (!(getcwd(pwd, 1024)))
	{
		tmp = get_key("PWD", params->env);
		if (!tmp)
		{
			write(2, "we can't get the working directory\n", 35);
			return (1);
		}
		else
			printf("%s\n", get_key("PWD", params->env));
	}
	else
		printf("%s\n", pwd);
	free (pwd);
	return (0);
}

int	trying_with_pwd(t_params *params)
{
	char	*pwd;

	pwd = malloc(1024 * (sizeof(char)));
	if (!pwd)
	{
		perror("malloc");
		return (1);
	}
	if (!(getcwd(pwd, 1024)))
	{
		write(2, "some thing went wrong here\n", 28);
		return (1);
	}
	else
		search_and_replace("PWD", pwd, &(params->env), 1);
	return (0);
}

int	check_deleted(t_params *params, char *tmp2)
{
	struct stat	the_path;
	char		*tmp;

	tmp = get_key("PWD", params->env);
	stat(tmp, &the_path);
	if (!S_ISDIR(the_path.st_mode))
	{
		chdir("..");
		write(2, "cd: error retrieving current ", 29);
		write(2, "directory: getcwd: cannot\n", 26);
		search_and_replace("OLDPWD",
			ft_copy(get_key("PWD", params->env)), &(params->env), 1);
		if (access(tmp2, F_OK) != -1)
			search_and_replace("PWD", tmp2, &(params->env), 1);
		else
		{
			search_and_replace("PWD",
				ft_strjoin2(tmp, "/.."), &(params->env), 1);
			free (tmp2);
		}
		return (1);
	}
	return (0);
}

char	*ft_spliter(char *s, int j)
{
	int	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s) - 1;
	while (s[i] && (s[i] == '/' || s[i] == '.'))
		i--;
	while (s[i] && (s[i] != '/'))
		i--;
	return (ft_substr(s, 0, i - (j * 2)));
}

int	change_dir(t_parse *st, t_params *params, char *s)
{
	struct stat	the_path;
	char		*tmp;
	static int	i = 0;

	stat(s, &the_path);
	tmp = ft_spliter(get_key("PWD", params->env), i);
	if (!tmp)
	{
		if (trying_with_pwd(params))
			return (1);
	}
	if (tmp && access(tmp, F_OK) == -1 && !(ft_strcmp("..", st->cmd[1])))
	{
		check_deleted(params, tmp);
		i++;
		return (1);
	}
	else if (S_ISDIR(the_path.st_mode) && access(s, X_OK) == -1)
		return (print_error("cd", ": Permission denied\n", s), 1);
	else if (!S_ISDIR(the_path.st_mode) && access(s, F_OK) != -1)
		return (print_error("cd", ": not a directory\n", s), 1);
	else if (chdir(s) == -1)
		return (print_error("cd", ": no such file or directory\n", s), 1);
	else
	{
		change_pwd_value(params);
		free (tmp);
		i = 0;
	}
	return (0);
}
