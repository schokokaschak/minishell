/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_recursion_depth.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 12:22:09 by nradin            #+#    #+#             */
/*   Updated: 2023/04/09 12:23:54 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	get_max_depth(t_token_list *tokens)
{
	int	opened;
	int	depth;

	opened = 0;
	depth = 0;
	while (tokens)
	{
		if (tokens->type == PRNTH_RIGHT)
			depth--;
		if (depth < 0)
			return (-1);
		if (tokens->type == PRNTH_LEFT)
		{
			opened++;
			depth++;
		}
		tokens = tokens->next;
	}
	if (depth != 0)
		return (-1);
	return (opened);
}

void	get_prnth_count(t_token_list *tokens, int len, int *op, int *cl)
{
	int	i;

	i = 0;
	*op = 0;
	*cl = 0;
	while (tokens && i < len)
	{
		if (tokens->type == PRNTH_LEFT)
			(*op)++;
		if (tokens->type == PRNTH_RIGHT)
			(*cl)++;
		tokens = tokens->next;
		i++;
	}
}

int	set_recursion_depth(t_log_groups *log_group)
{
	int	max_depth;
	int	cur_depth;
	int	op;
	int	cl;

	max_depth = get_max_depth(log_group->tokens);
	if (max_depth == -1)
	{
		perror("parse error");
		return (-1);
	}
	cur_depth = max_depth;
	while (log_group)
	{
		get_prnth_count(log_group->tokens, log_group->token_count, &op, &cl);
		cur_depth -= op;
		log_group->rec_depth = max_depth - cur_depth;
		cur_depth += cl;
		log_group = log_group->next;
	}
	return (1);
}
