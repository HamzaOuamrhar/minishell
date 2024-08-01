/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:28:03 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/07/30 10:45:30 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGQUIT)
		return ;
	if (!(waitpid(-1, NULL, WNOHANG)))
	{
		write(1, "\n", 1);
		return ;
	}
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	_g_signal = 130;
	return ;
}

void	signal_handle(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
