/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:01:24 by iez-zagh          #+#    #+#             */
/*   Updated: 2024/08/05 12:04:20 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fork_failure(t_params *params)
{
	if (params->pid == -1)
	{
		g_status = 1;
		write(2, "fork: Resource temporarily unavailable", 38);
		return (1);
	}
	return (0);
}
