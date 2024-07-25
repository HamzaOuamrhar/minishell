/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:28:03 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/07/25 19:20:28 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		puts("this is  a signal");
		printf("\n");
		rl_replace_line();
		return ;
	}
	else if (sig == SIGQUIT)
	{
		puts("sigquit");
		// freeing(st, params); //need to free
		exit(0);
	}
}

void	signal_handle(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

