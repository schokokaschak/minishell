/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_group.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:27:33 by akashets          #+#    #+#             */
/*   Updated: 2023/03/27 12:36:44 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	check_log(t_token_list *token, int *needed)
{
	if (!token->prev)
		*needed = -1;
	else if (token->prev->type == LOGICAL_AND)
		*needed = 1;
	else if (token->prev->type == LOGICAL_OR)
		*needed = 0;
}

t_log_groups	*create_log_group(t_token_list **token)
{
	t_log_groups	*new;
	int				i;
	t_token_list	*buf;

	buf = *token;
	i = 0;
	new = malloc(sizeof(t_log_groups));
	if (new == NULL)
		return (NULL);
	new->tokens = *token;
	new->needed = -2;
	check_log(buf, &new->needed);
	while (buf && !is_log_group(buf->type))
	{
		i++;
		buf = buf->next;
	}
	new->token_count = i;
	new->pipe_groups = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	add_log_group(t_log_groups **exists, t_log_groups *new)
{
	t_log_groups	*cur;

	if (!new)
		return (-1);
	if (!(*exists))
		*exists = new;
	else
	{
		cur = *exists;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
		new->prev = cur;
	}
	return (1);
}

int	init_log_group(t_data *new, t_token_list **tokens, \
					t_token_list *cur, t_token_list *buf)
{
	cur = *tokens;
	while (cur && !is_log_group(cur->type))
		cur = cur->next;
	if (add_log_group(&new->log_groups, create_log_group(tokens)) == -1)
		return (-1);
	if (!cur)
		return (1);
	cur = cur->next;
	new->i = 0;
	while (cur)
	{
		if (new->i == 0)
			buf = cur;
		if (is_log_group(cur->type) || cur->next == NULL)
		{
			if (add_log_group(&new->log_groups, create_log_group(&buf)) == -1)
				return (-1);
			new->i = -1;
		}
		new->i++;
		cur = cur->next;
	}
	return (1);
}
