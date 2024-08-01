/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:28:03 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/01 17:12:39 by iez-zagh         ###   ########.fr       */
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
	g_status = 130;
	return ;
}

void	signal_handle(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
