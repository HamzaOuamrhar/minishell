#include "minishell.h"

void	count_things(t_token **tokens, t_count *count)
{
	count->in = 0;
	count->out = 0;
	count->app = 0;
	count->words = 0;
	if (*tokens && ft_strcmp((*tokens)->type, "PIPE") == 0)
		*tokens = (*tokens)->next;
	while (*tokens && ft_strcmp((*tokens)->type, "PIPE") != 0)
	{
		if (ft_strcmp((*tokens)->type, "WORD") == 0 && (!white_word((*tokens)->value) || (*tokens)->wh == 1))
			count->words ++;
		else if (ft_strcmp((*tokens)->type, "INPUT") == 0)
			count->in ++;
		else if (ft_strcmp((*tokens)->type, "OUTPUT") == 0)
			count->out ++;
		else if (ft_strcmp((*tokens)->type, "APPEND") == 0)
			count->app ++;
		*tokens = (*tokens)->next;
	}
}

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

void	initialize_parse(t_decl3 *decl, t_count *count, t_parse **new_parse, t_parse **parse)
{
	decl->i = 0;
	decl->j = 0;
	decl->k = 0;
	decl->z = 0;
	decl->l = 0;
	(*new_parse) = ft_malloc(sizeof(t_parse), 1);
	(*new_parse)->next = NULL;
	(*new_parse)->i = 0;
	if (decl->f_time)
		(*new_parse)->i = ++(*parse)->i;
	decl->f_time ++;
	(*new_parse)->cmd = ft_malloc((1 + count->words - count->in - count->out - count->app) * sizeof(char **), 1);
	(*new_parse)->in = ft_malloc((1 + count->in) * sizeof(char **), 1);
	(*new_parse)->out = ft_malloc((1 + count->out) * sizeof(char **), 1);
	(*new_parse)->app = ft_malloc((1 + count->app) * sizeof(char **), 1);
	(*new_parse)->in_dup = NULL;
	(*new_parse)->out_dup = NULL;
}

int	parser(t_token *tokens, t_parse **parse)
{
	t_parse	*new_parse;
	t_token	*copie;
	t_decl3	decl;
	t_count	count;

	copie = tokens;
	decl.f_time = 0;
	while (tokens)
	{
		count_things(&copie, &count);
		initialize_parse(&decl, &count, &new_parse, parse);
		while (tokens && ft_strcmp(tokens->type, "PIPE") != 0)
		{
			if (tokens && ft_strcmp(tokens->type, "WORD") == 0 && (!white_word(tokens->value) || tokens->wh == 1))
				new_parse->cmd[decl.i++] = ft_strdup(tokens->value);
			else if (tokens && ft_strcmp(tokens->type, "INPUT") == 0)
			{
				if (parse_input(&decl, &tokens, &new_parse))
					return (1);
			}
			else if (tokens && ft_strcmp(tokens->type, "OUTPUT") == 0)
			{
				if (parse_output(&decl, &tokens, &new_parse))
					return (1);
			}
			else if (tokens && ft_strcmp(tokens->type, "APPEND") == 0)
			{
				if (parse_append(&decl, &tokens, &new_parse))
					return (1);
			}
			else if (tokens && ft_strcmp(tokens->type, "HEREDOC") == 0)
				parse_heredoc(&decl, &tokens, &new_parse);
			if (tokens)
				tokens = tokens->next;
		}
		new_parse->cmd[decl.i] = NULL;
		new_parse->in[decl.j] = NULL;
		new_parse->out[decl.k] = NULL;
		new_parse->app[decl.z] = NULL;
		add_back_parse(parse, new_parse);
		if (tokens)
			tokens = tokens->next;
	}
	return (0);
}
