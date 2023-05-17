/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:36:31 by nradin            #+#    #+#             */
/*   Updated: 2023/04/02 20:39:47 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handle);
}

void	heredoc_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_sig_handle);
}

void	child_sig(void)
{
	signal(SIGQUIT, sig_handle_child);
	signal(SIGINT, sig_handle_child);
}
