#include "../minishell.h"

void	expand_line(char **line, t_params *params)
{
	int	i;
	char	*value;
	char	*n_l_v;
	int		first;

	n_l_v = NULL;
	i = 0;
	while ((*line)[i])
	{
		first = i;
		while ((*line)[i] && (*line)[i] != '$')
			i++;
		n_l_v = ft_strjoin(n_l_v, ft_mysubstr(*line, first, i - first));
		if ((*line)[i])
			i++;
		first = i;
		if (!is_alph((*line)[i]) || (*line)[i] != '_')
			i++;
		while ((*line)[i] && (is_alph_num((*line)[i]) || (*line)[i] == '_'))
			i++;
		value = get_key(ft_mysubstr(*line, first, i - first), params->env);
		if (value)
			n_l_v = ft_strjoin(n_l_v, value);
		else
			n_l_v = ft_strjoin(n_l_v, "");
	}
	*line = n_l_v;
}
