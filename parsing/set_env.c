#include "minishell.h"

t_env	*last_var(t_env *env_vars)
{
	t_env	*tmp;

	tmp = env_vars;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_var(t_env **env_vars, t_env *new)
{
	if (!*env_vars)
		*env_vars = new;
	else
		last_var(*env_vars)->next = new;
}

void	set_env(t_env **env_vars, char **env)
{
	t_env	*new_var;
	int	start;
	int	end;
	int i = 0;
	int	j = 0;
	while(env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		start = j + 1;
		end = ft_strlen(env[i]);
		new_var = ft_malloc(sizeof(t_env), 1);
		new_var->key = ft_substr(env[i], 0, j);
		new_var->value = ft_substr(env[i], start, end - start);
		new_var->next = NULL;
		add_var(env_vars, new_var);
		i++;
	}
}