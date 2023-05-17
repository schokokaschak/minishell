/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_group.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:40:48 by akashets          #+#    #+#             */
/*   Updated: 2023/03/27 12:40:59 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

t_pipe_groups	*create_pipe_group(t_token_list **token)
{
	t_pipe_groups	*new;
	int				i;
	t_token_list	*buf;

	buf = *token;
	i = 0;
	new = malloc(sizeof(t_pipe_groups));
	if (new == NULL)
		return (NULL);
	new->tokens = *token;
	while (buf && !is_group(buf->type))
	{
		i++;
		buf = buf->next;
	}
	new->token_count = i;
	new->cmnd = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	add_pipe_group(t_pipe_groups **exists, t_pipe_groups *new)
{
	t_pipe_groups	*cur;

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

int	init_pipe_group(t_data *new)
{
	t_log_groups	*cur;
	t_token_list	*worker;

	cur = new->log_groups;
	while (cur)
	{
		worker = cur->tokens;
		new->i = -1;
		if (add_pipe_group(&cur->pipe_groups, create_pipe_group(&worker)) == -1)
			return (-1);
		while (++new->i < cur->token_count)
		{
			if (is_group(worker->type))
				if (add_pipe_group(&cur->pipe_groups, \
							create_pipe_group(&worker->next)) == -1)
					return (-1);
			worker = worker->next;
		}
		cur = cur->next;
	}
	return (1);
}
