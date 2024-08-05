/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iez-zagh <iez-zagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:04:27 by houamrha          #+#    #+#             */
/*   Updated: 2024/08/05 14:43:27 by iez-zagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(char *error_msg)
{
	g_status = 258;
	printf("%s\n", error_msg);
}

void	add_middle_n(t_token **token, char *value)
{
	t_token	*tmp;
	t_token	*new;

	new = ft_malloc(sizeof(t_token), 1);
	new->next = NULL;
	new->type = ft_strdup("WORD");
	new->value = value;
	if (white_word(value))
		new->wh = 1;
	tmp = (*token)->next;
	(*token)->flag = 1;
	(*token)->next = new;
	new->next = tmp;
	*token = (*token)->next;
}
