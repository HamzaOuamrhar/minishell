#include "../minishell.h"

int	count_args(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	change_dir(t_parse *st, t_params *params, char *s)
{
	struct stat the_path;
	char		*tmp;
	
	stat(s, &the_path);
	if (access(st->cmd[0], X_OK) == -1 && !(ft_strcmp("..", st->cmd[1])))
	{
		tmp = get_key("OLPDWD", params->env);
		printf("%s\n", tmp);
		chdir(tmp);
		free (tmp);
		change_pwd_value(params);
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
