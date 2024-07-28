/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:28:03 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/07/28 17:21:10 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGQUIT)
		return ;
	if (!(waitpid(-1, NULL, WNOHANG))) // do not wait for any child process
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

void	signal_handle()
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
//handle the herdoc alone

// void	hanlde_signint(int sig)
// {
	
// }