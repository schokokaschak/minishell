/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 10:42:42 by nradin            #+#    #+#             */
/*   Updated: 2023/04/01 17:39:43 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	sub_extend_token(t_token_list *cur, char **seps, int *index)
{
	int	i;

	i = 0;
	while (seps[i])
	{
		if (ft_strncmp(seps[i], cur->token, cur->len) == 0)
		{
			cur->type = index[i];
			break ;
		}
		i++;
		if (i == 7)
		{
			perror("unkown separator");
			return (-1);
		}
	}
	return (1);
}

int	extend_token(t_token_list *token)
{
	t_token_list	*cur;
	char			*seps[7];
	int				index[7];

	init_seps(seps);
	init_index(index);
	cur = token;
	while (cur)
	{
		if (cur->type == SEPAR_MORE || cur->type == SEPAR_PIPE \
			|| cur->type == LOGICAL_AND || cur->type == SEPAR_LESS)
			if (sub_extend_token(cur, seps, index) == -1)
				return (-1);
		cur = cur->next;
	}
	return (1);
}

void	check_for_token(int *type, char *cur, \
	char **start, t_token_list	**tokens)
{
	if (*type == PRNTH_LEFT)
		add_common_tok(type, cur, start, tokens);
	else if (*type == PRNTH_RIGHT)
		add_common_tok(type, cur, start, tokens);
	else if (*type != SING_QUOTES && *type != DUP_QUOTES \
						&& *type != get_type(*cur))
		add_common_tok(type, cur, start, tokens);
}

int	check_for_quot_token(int *type, char *cur, \
	char **start, t_token_list	**tokens)
{
	int	ret;

	ret = 0;
	if (get_type(*cur) == DUP_QUOTES || get_type(*cur) == SING_QUOTES)
	{
		ret = add_quot_tok(type, cur, start, tokens);
		if (ret == -1)
		{
			free_tokens(*tokens);
			return (-1);
		}
	}
	return (ret);
}

t_token_list	*lexer(char *input)
{
	int				i;
	int				type;
	char			*start;
	t_token_list	*tokens;
	int				temp;

	if (!input)
		return (NULL);
	i = 0;
	tokens = NULL;
	type = get_type(input[i]);
	start = input;
	while (input[i])
	{
		check_for_token(&type, &input[i], &start, &tokens);
		temp = check_for_quot_token(&type, &input[i], &start, &tokens);
		if (temp == -1)
			return (NULL);
		i += temp + 1;
	}
	add_token(&tokens, create_token(type, start, (int)(&input[i] - start)));
	if (extend_token(tokens) == -1)
		return (free_tokens(tokens));
	return (tokens);
}
