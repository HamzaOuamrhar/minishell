/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:28:03 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/06 15:30:22 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGQUIT)
		return ;
	if (!(waitpid(-1, NULL, WNOHANG)))
	{
		g_status = 130;
		return ;
	}
	g_status = 2;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handle(t_params *params)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	if (g_status == 130)
		params->status = 130;
}

void	signal_handle2(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	minishell(t_parse *st)
{
	char	*tmp;

	tmp = ft_substr(st->cmd[0], 2, ft_strlen(st->cmd[0]));
	if (!access(tmp, X_OK))
	{
		st->com_path = ft_copy(st->cmd[0]);
		free (tmp);
		return (1);
	}
	return (0);
}

void	malloc_error(t_params *params)
{
	perror("malloc");
	freeing(params);
	ft_malloc(3, 0);
	exit (1);
}
