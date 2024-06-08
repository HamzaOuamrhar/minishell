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
	while(tmp[i] && tmp[i] != '/')
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
	search_and_replace("OLDPWD", ft_copy(get_key("PWD", params->env)), &(params->env), 1);
	search_and_replace("PWD", tmp2, &(params->env), 1);
	return ;
}

void	change_dir(t_parse *st, t_params *params, char *s)
{
	struct stat the_path;
	
	stat(s, &the_path);
	if (access(get_key("PWD", params->env), X_OK) == -1 && !(ft_strcmp("..", st->cmd[1])))
	{
		no_permissions(params);
		return ;
	}
	if (S_ISDIR(the_path.st_mode) && access(s, X_OK) == -1)
	{
		printf("shellantics: cd: %s: Permission denied\n", s);
		return ;
	}
	if (!S_ISDIR(the_path.st_mode) && access(s, F_OK) != -1)
	{
		printf("cd: not a directory: %s\n", s);
		return ;
	}
	if (chdir(s) == -1)
	{
		printf("cd: no such file or directory: %s\n", s);
		return ;
	}
	else
		change_pwd_value(params);
}
