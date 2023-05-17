/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:46:02 by nradin            #+#    #+#             */
/*   Updated: 2023/04/05 14:37:57 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\nminishell : ", 1);
	}
}

void	heredoc_sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		exit(EXIT_FAILURE);
	}
}

void	sig_handle_child(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	}
	if (sig == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
