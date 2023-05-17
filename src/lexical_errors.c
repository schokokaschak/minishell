/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:20:21 by nradin            #+#    #+#             */
/*   Updated: 2023/03/19 13:27:56 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	check_group_pos(t_token_list *tokens)
{
	int	looking_for_word;

	looking_for_word = 0;
	if (is_group(tokens->type))
		return (-1);
	while (tokens)
	{
		if (is_group(tokens->type) && looking_for_word)
			return (-1);
		if ((tokens->type == TEXT || tokens->type == DUP_QUOTES \
			|| tokens->type == SING_QUOTES) && looking_for_word)
			looking_for_word = 0;
		if (is_group(tokens->type) && !looking_for_word)
			looking_for_word = 1;
		tokens = tokens->next;
	}
	if (looking_for_word)
		return (-1);
	return (1);
}

int	check_tok_content(t_token_list *tokens)
{
	while (tokens)
	{
		if (tokens->type == PIPE && tokens->len != 1)
			return (-1);
		if ((tokens->type == LOGICAL_AND || tokens->type == LOGICAL_OR) \
													&& tokens->len != 2)
			return (-1);
		if ((tokens->type == HERE_DOC || tokens->type == OUTPUT_APPEND) \
													&& tokens->len != 2)
			return (-1);
		if ((tokens->type == INPUT || tokens->type == OUTPUT_OVER) \
													&& tokens->len != 1)
			return (-1);
		if (is_prnth(tokens->type) && tokens->next \
					&& is_prnth(tokens->next->type))
			if (tokens->type != tokens->next->type)
				return (-1);
		tokens = tokens->next;
	}
	return (1);
}

int	check_redir_dest(t_token_list *tokens)
{
	int	looking_for_dest;

	looking_for_dest = 0;
	while (tokens)
	{
		if ((is_redir(tokens->type) || is_group(tokens->type)) \
				&& looking_for_dest)
			return (-1);
		if ((tokens->type == TEXT || tokens->type == DUP_QUOTES \
			|| tokens->type == SING_QUOTES) && looking_for_dest)
			looking_for_dest = 0;
		if (is_redir(tokens->type) && !looking_for_dest)
			looking_for_dest = 1;
		tokens = tokens->next;
	}
	if (looking_for_dest)
		return (-1);
	return (1);
}

int	check_prnth_location(t_token_list *t)
{
	int	logical_char;
	int	valid_prnth;
	int	on_prnth;

	if (is_prnth(t->type) || (t->type == SPACE && \
			t->next && is_prnth(t->next->type)))
		logical_char = 1;
	on_prnth = 0;
	valid_prnth = 0;
	while (t)
	{
		if (logical_char != 1 && is_prnth(t->type))
			logical_char = 1;
		prnth_loc_if_state(t, &on_prnth, &logical_char, &valid_prnth);
		if (on_prnth && !is_prnth(t->type) && t->type != SPACE && \
														!is_log_group(t->type))
		{
			if (valid_prnth)
				cancel_prnth_loc(&logical_char, &on_prnth, &valid_prnth);
			else
				return (-1);
		}
		t = t->next;
	}
	return (0);
}

int	lexical_errors(t_token_list *tokens)
{
	int	flag;

	flag = 0;
	if (!flag && check_group_pos(tokens) == -1)
		flag = 1;
	if (!flag && check_tok_content(tokens) == -1)
		flag = 1;
	if (!flag && check_redir_dest(tokens) == -1)
		flag = 1;
	if (!flag && check_prnth_location(tokens) == -1)
		flag = 1;
	if (flag)
	{
		perror("Lexical error");
		free_tokens(tokens);
		return (-1);
	}
	return (1);
}
