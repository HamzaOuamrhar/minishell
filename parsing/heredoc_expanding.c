#include "../minishell.h"

static void	set_value(char **line, t_params *params, t_decl2 *decl)
{
	if ((*line)[decl->start] == '?')
		decl->value = ft_strdup(ft_itoa(_g_signal));
	else
		decl->value = get_key(fmysubstr(*line,
					decl->start, decl->i - decl->start), params->env);
	if (decl->value)
		decl->n_t_v = ft_strjoin(decl->n_t_v, decl->value);
	else
		decl->n_t_v = ft_strjoin(decl->n_t_v, "");
}

void	expand_line(char **line, t_params *params)
{
	t_decl2	decl;

	42 && (decl.n_t_v = NULL, decl.i = 0);
	while ((*line)[decl.i])
	{
		decl.start = decl.i;
		while ((*line)[decl.i] && (*line)[decl.i] != '$')
			decl.i++;
		decl.n_t_v = ft_strjoin(decl.n_t_v,
				fmysubstr(*line, decl.start, decl.i - decl.start));
		if ((*line)[decl.i])
			decl.i++;
		decl.start = decl.i;
		if ((*line)[decl.i]
				&& !is_alph((*line)[decl.i]) && (*line)[decl.i] != '_')
			decl.i++;
		else
		{
			while ((*line)[decl.i]
				&& (is_alph_num((*line)[decl.i]) || (*line)[decl.i] == '_'))
				decl.i++;
		}
		set_value(line, params, &decl);
	}
	*line = decl.n_t_v;
}
