#include "../minishell.h"

void	parser_reset(t_parse **st)
{
	while (*st)
	{
		if ((*st)->in_fd)
			close((*st)->in_fd);
		(*st) = (*st)->next;
	}
}

int	check_in_files(t_parse *st, t_params *params)
{
	if (check_perms(st, params))
		return (1);
	return (0);
}


void	starting_excute(t_parse *st, t_params *params, t_token *token)
{
	if (!syntax(token))
	{
		expander(token, *params);
		if (!parser(token, &st, params))
		{
			// tokens_reset(&token);
			// parser_reset(&st);
			// continue;
			return ;
		}
		params->cmds = lstsize(st);
		while (st)
		{
			update_(st, params);
			excute_cmds(st, params, token); //here the super hero
			st = st->next;
			params->i++;
		}
		while (waitpid(-1, NULL, 0) > 0 || errno != ECHILD)
			;
		initialiaze_vars(params, &token, 0);
	}

}

void	wait_prompt1(t_params *params)
{
	t_token		*token;
	t_parse		*st;

	initialiaze_vars(params, &token, 1);
	st = NULL;
	token = NULL;
	while (1)
	{
		signal_handle();
		params->q = 0;
		params->line = readline("• Shellantics$ ");
		if (!params->line)
			break ; // exit with 1
		add_history(params->line);
		tokenize(&token, params->line, &params->q);
		if (!params->q)
			starting_excute(st, params, token);
		tokens_reset(&token);
		parser_reset(&st);
	}
}