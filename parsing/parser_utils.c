#include "minishell.h"

int	parse_input(t_decl3 *decl, t_token **tokens, t_parse **new_parse)
{
	if (ft_strcmp((*tokens)->next->type, "WHITE") == 0)
		*tokens = (*tokens)->next;
	if ((*tokens)->next->flag)
	{
		exit_syntax_error("shellantics: ambiguous redirect");
		return (1);
	}
	(*new_parse)->in[decl->j++] = ft_strdup((*tokens)->next->value);
	(*new_parse)->in_dup = (*new_parse)->in[decl->j - 1];
	(*tokens) = (*tokens)->next;
	return (0);
}

int	parse_output(t_decl3 *decl, t_token **tokens, t_parse **new_parse)
{
	if (ft_strcmp((*tokens)->next->type, "WHITE") == 0)
		(*tokens) = (*tokens)->next;
	if ((*tokens)->next->flag)
	{
		exit_syntax_error("shellantics: ambiguous redirect");
		return (1);
	}
	(*new_parse)->out[decl->k++] = ft_strdup((*tokens)->next->value);
	(*new_parse)->out_dup = (*new_parse)->out[decl->k - 1];
	(*tokens) = (*tokens)->next;
	return (0);
}

int	parse_append(t_decl3 *decl, t_token **tokens, t_parse **new_parse)
{
	if (ft_strcmp((*tokens)->next->type, "WHITE") == 0)
		(*tokens) = (*tokens)->next;
	if ((*tokens)->next->flag)
	{
		exit_syntax_error("shellantics: ambiguous redirect");
		return (1);
	}
	(*new_parse)->app[decl->z++] = ft_strdup((*tokens)->next->value);
	(*new_parse)->out_dup = (*new_parse)->app[decl->z - 1];
	(*tokens) = (*tokens)->next;
	return (0);
}

void	parse_heredoc(t_decl3 *decl, t_token **tokens, t_parse **new_parse)
{
	(*new_parse)->i ++;
	if (ft_strcmp((*tokens)->next->type, "WHITE") == 0)
		(*tokens) = (*tokens)->next;
	(*new_parse)->in_dup = ft_strjoin("h", ft_itoa((*new_parse)->i));
	decl->fd = open(ft_strjoin("/tmp/", (*new_parse)->in_dup), O_CREAT | O_RDWR | O_TRUNC, 0777);
	unlink(ft_strjoin("/tmp/", (*new_parse)->in_dup));
	while(1)
	{
		decl->line = readline("> ");
		if (!decl->line)
			break;
		if (ft_strcmp((*tokens)->next->value, decl->line) == 0)
			break;
		if (!(*tokens)->next->has_q && in_str(decl->line, '$'))
			expand_line(&decl->line);
		write(decl->fd, decl->line, ft_strlen(decl->line));
		write(decl->fd, "\n", 1);
	}
	(*tokens) = (*tokens)->next;
}
