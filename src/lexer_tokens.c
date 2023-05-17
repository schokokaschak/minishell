/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:59:37 by nradin            #+#    #+#             */
/*   Updated: 2023/03/30 11:31:03 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

t_token_list	*create_token(int type, char *start, int len)
{
	t_token_list	*new;

	if (!len && !(type == DUP_QUOTES || type == SING_QUOTES))
		return (NULL);
	new = malloc(sizeof(t_token_list));
	new->len = len;
	new->type = type;
	new->token = start;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_token(t_token_list **tokens, t_token_list *new_token)
{
	t_token_list	*cur;

	if (!new_token)
		return ;
	if (!(*tokens))
		*tokens = new_token;
	else
	{
		cur = *tokens;
		while (cur->next)
			cur = cur->next;
		cur->next = new_token;
		new_token->prev = cur;
	}
}

void	free_token(t_token_list *token)
{
	if (token->type == EXTENDED_QUOT || token->type == EXTENDED_TEXT)
		free(token->token);
	free(token);
}
