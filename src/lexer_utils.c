/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:39:37 by nradin            #+#    #+#             */
/*   Updated: 2023/04/01 17:35:15 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	init_seps(char **separs)
{
	separs[0] = ">";
	separs[1] = "<";
	separs[2] = ">>";
	separs[3] = "<<";
	separs[4] = "|";
	separs[5] = "&&";
	separs[6] = "||";
}

void	init_index(int *index)
{
	index[0] = OUTPUT_OVER;
	index[1] = INPUT;
	index[2] = OUTPUT_APPEND;
	index[3] = HERE_DOC;
	index[4] = PIPE;
	index[5] = LOGICAL_AND;
	index[6] = LOGICAL_OR;
}

int	get_type(char c)
{
	if (ft_isspace(c))
		return (SPACE);
	if (c == '|')
		return (SEPAR_PIPE);
	if (c == '>')
		return (SEPAR_MORE);
	if (c == '<')
		return (SEPAR_LESS);
	if (c == '(')
		return (PRNTH_LEFT);
	if (c == ')')
		return (PRNTH_RIGHT);
	if (c == '\'')
		return (SING_QUOTES);
	if (c == '\"')
		return (DUP_QUOTES);
	if (c == '&')
		return (LOGICAL_AND);
	return (TEXT);
}

int	add_quot_tok(int *type, char *cur, char **start, t_token_list	**tokens)
{
	int	i;

	i = 1;
	while (cur[0] != cur[i])
	{
		if (cur[i] == '\0')
		{
			perror("Quotes are not closed!");
			return (-1);
		}
		i++;
	}
	if (i == 1)
		add_token(tokens, create_token(*type, *start, 0));
	else
		add_token(tokens, create_token(*type, *start + 1, i - 1));
	*start = &cur[i] + 1;
	*type = get_type(cur[i + 1]);
	return (i);
}

void	add_common_tok(int *type, char *cur, char **start, \
									t_token_list	**tokens)
{
	add_token(tokens, create_token(*type, *start, (int)(cur - *start)));
	*start = cur;
	*type = get_type(*cur);
}
