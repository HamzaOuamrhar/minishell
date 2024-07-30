/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:02:58 by houamrha          #+#    #+#             */
/*   Updated: 2024/07/30 11:03:01 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax(t_token *token)
{
	if (pipe_syntax(token))
		return (1);
	if (redirection_syntax(token))
		return (1);
	return (0);
}
