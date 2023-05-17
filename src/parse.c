/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:17:43 by nradin            #+#    #+#             */
/*   Updated: 2023/04/07 21:21:26 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	parse_checkers(t_data *new, int *last_exit)
{
	new->i = 0;
	new->flag = 0;
	if (set_recursion_depth(new->log_groups) == -1)
		return (0);
	if (init_pipe_group(new) == -1)
		return (0);
	if (init_commands(new, last_exit) == -1)
		return (0);
	return (1);
}

t_data	*parse(t_token_list **tokens, int *last_exit, char *in)
{
	t_data			*new;
	t_token_list	*cur;
	t_token_list	*buf;

	new = malloc(sizeof(t_data));
	if (lexical_errors(*tokens) == -1)
	{
		*last_exit = 2;
		return (NULL);
	}
	cur = *tokens;
	buf = NULL;
	new->log_groups = NULL;
	if (parse_extensions(*tokens, last_exit) == -1)
		return (NULL);
	if (extend_wildcards(*tokens) == -1)
		return (NULL);
	if (init_log_group(new, tokens, cur, buf) == -1)
		return (NULL);
	if (parse_checkers(new, last_exit) == 0)
	{
		free_data_in_loop(new, in);
		return (NULL);
	}
	return (new);
}
