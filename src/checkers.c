/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:38:36 by nradin            #+#    #+#             */
/*   Updated: 2023/03/27 14:42:55 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	is_group(int type)
{
	if (type == PIPE || type == LOGICAL_AND || type == LOGICAL_OR)
		return (1);
	return (0);
}

int	is_log_group(int type)
{
	if (type == LOGICAL_AND || type == LOGICAL_OR)
		return (1);
	return (0);
}

int	is_prnth(int type)
{
	if (type == PRNTH_LEFT || type == PRNTH_RIGHT)
		return (1);
	return (0);
}

int	is_redir(int type)
{
	if (type == INPUT || type == OUTPUT_APPEND \
			|| type == OUTPUT_OVER || type == HERE_DOC)
		return (1);
	return (0);
}

int	check_types(char *argv, int k)
{
	if (!ft_strncmp(argv, "|", 1) && k == 0)
		return (1);
	else if (!ft_strncmp(argv, "&&", 2) && k == 0)
		return (1);
	else
		return (0);
}
