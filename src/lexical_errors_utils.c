/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_errors_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:05:47 by nradin            #+#    #+#             */
/*   Updated: 2023/03/27 12:43:38 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	cancel_prnth_loc(int *l, int *o, int *p)
{
	if (p)
		*p = 0;
	if (o)
		*o = 0;
	if (l)
		*l = 0;
}

void	prnth_loc_if_state(t_token_list *t, int *on_prnth, \
	int *logical_char, int *valid_prnth)
{
	if (!is_prnth(t->type) && t->type != SPACE)
		*logical_char = 0;
	if (is_prnth(t->type))
		*on_prnth = 1;
	if (is_log_group(t->type))
		*logical_char = 1;
	if (*logical_char && *on_prnth)
		*valid_prnth = 1;
}

int	ctrl_d_exit(void)
{
	clear_history();
	free_argv(g_envp);
	ft_putstr_fd("\b\bexit", 1);
	return (1);
}

int	free_input(char *input)
{
	if (input)
		free(input);
	return (1);
}
