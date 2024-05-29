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

void	parser(t_token *tokens, t_parse **parse)
{
	int	i;
	int j;
	int k;
	int z;
	int	l;
	t_parse	*new_parse;
	t_token	*copie;
	t_count	count;
	char 	*line;
	int		fd;
	int		f_time;

	copie = tokens;
	f_time = 0;
	while (tokens)
	{
		i = 0;
		j = 0;
		k = 0;
		z = 0;
		l = 0;
		new_parse = malloc(sizeof(t_parse));
		new_parse->next = NULL;
		new_parse->i = 0;
		if (f_time)
			new_parse->i = ++(*parse)->i;
		f_time ++;
		count_things(&copie, &count);
		new_parse->cmd = malloc((1 + count.words - count.in - count.out - count.app) * sizeof(char **));
		new_parse->in = malloc((1 + count.in) * sizeof(char **));
		new_parse->out = malloc((1 + count.out) * sizeof(char **));
		new_parse->app = malloc((1 + count.app) * sizeof(char **));
		new_parse->in_dup = NULL;
		new_parse->out_dup = NULL;
		while (tokens && ft_strcmp(tokens->type, "PIPE") != 0)
		{
			if (tokens && ft_strcmp(tokens->type, "WORD") == 0 && (!white_word(tokens->value) || tokens->wh == 1))
				new_parse->cmd[i++] = ft_strdup(tokens->value);
			else if (tokens && ft_strcmp(tokens->type, "INPUT") == 0)
			{
				if (ft_strcmp(tokens->next->type, "WHITE") == 0)
					tokens = tokens->next;
				new_parse->in[j++] = ft_strdup(tokens->next->value);
				new_parse->in_dup = new_parse->in[j - 1];
				tokens = tokens->next;
			}
			else if (tokens && ft_strcmp(tokens->type, "OUTPUT") == 0)
			{
				if (ft_strcmp(tokens->next->type, "WHITE") == 0)
					tokens = tokens->next;
				new_parse->out[k++] = ft_strdup(tokens->next->value);
				new_parse->out_dup = new_parse->out[k - 1];
				tokens = tokens->next;
			}
			else if (tokens && ft_strcmp(tokens->type, "APPEND") == 0)
			{
				if (ft_strcmp(tokens->next->type, "WHITE") == 0)
					tokens = tokens->next;
				new_parse->app[z++] = ft_strdup(tokens->next->value);
				new_parse->out_dup = new_parse->app[z - 1];
				tokens = tokens->next;
			}
			else if (tokens && ft_strcmp(tokens->type, "HEREDOC") == 0)
			{
				new_parse->i ++;
				if (ft_strcmp(tokens->next->type, "WHITE") == 0)
					tokens = tokens->next;
				new_parse->in_dup = ft_strjoin(ft_strdup(tokens->next->value), ft_itoa(new_parse->i));
				fd = open(ft_strjoin("/tmp/", new_parse->in_dup), O_CREAT | O_RDWR | O_TRUNC, 0777);
				// unlink(ft_strjoin("/tmp/", new_parse->in_dup));
				while(1)
				{
					line = readline("> ");
					if (!line)
						break;
					if (ft_strcmp(tokens->next->value, line) == 0)
						break;
					expand_line(&line);
					write(fd, line, ft_strlen(line));
					write(fd, "\n", 1);
				}
				tokens = tokens->next;
			}
			if (tokens)
				tokens = tokens->next;
		}
		new_parse->cmd[i] = NULL;
		new_parse->in[j] = NULL;
		new_parse->out[k] = NULL;
		new_parse->app[z] = NULL;
		add_back_parse(parse, new_parse);
		if (tokens)
			tokens = tokens->next;
	}
}