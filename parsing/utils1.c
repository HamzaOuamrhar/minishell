#include "minishell.h"

char	*get_path_variable(char **env)
{
	char	*s;
	int		i;

	s = "PATH";
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(s, env[i], 4) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*get_acc_path(char **paths, char *com)
{
	int		i;
	char	*r;
	char	*rr;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		r = ft_strjoin(paths[i], "/");
		rr = ft_strjoin(r, com);
		free(r);
		if (access(rr, F_OK | X_OK) == 0)
			return (rr);
		i++;
		free(rr);
	}
	return (NULL);
}

char	*get_com_path(char **env, char *com)
{
	char *paths = get_path_variable(env) + 5;
	char **paths_array = ft_split(paths, ':');
	char *com_path = get_acc_path(paths_array, com);
	return (com_path);
}
