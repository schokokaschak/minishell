/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 15:59:21 by nradin            #+#    #+#             */
/*   Updated: 2023/04/05 12:39:58 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	init_wildcard_vars(int *i, int *j, int *wild, t_string_list **cur_wild)
{
	*i = 0;
	*j = 0;
	*wild = 0;
	*cur_wild = NULL;
	add_str_list(cur_wild, NULL);
	(*cur_wild)->str = malloc(1000);
}

int	check_token_ends(int *i, int *wild, \
	char *last_wild, t_token_list **cur)
{
	if (*i == (*cur)->len)
	{
		*cur = (*cur)->next;
		*i = 0;
		return (1);
	}
	if ((*cur)->token[*i] == '*' && ((*cur)->type == TEXT \
					|| (*cur)->type == EXTENDED_TEXT))
	{
		*last_wild = 0;
		*wild = 1;
		(*i)++;
		return (1);
	}
	return (0);
}

void	add_wild_comp(int *j, int *wild, t_string_list **cur_wild)
{
	if (*j != 0 && *wild)
	{
		add_str_list(cur_wild, NULL);
		*cur_wild = (*cur_wild)->next;
		(*cur_wild)->str = malloc(1000);
		*j = 0;
	}
}

void	check_start_end(t_token_list *token, t_wildcard *wildcard)
{
	int	i;

	if (token->token[0] == '*')
		wildcard->starting = 1;
	while (token->next && (token->next->type == EXTENDED_TEXT \
								|| token->next->type == TEXT))
		token = token->next;
	i = 0;
	while (token->token[i + 1])
		i++;
	if (token->token[i] == '*')
		wildcard->ending = 1;
}
