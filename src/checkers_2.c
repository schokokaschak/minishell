/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:38:36 by nradin            #+#    #+#             */
/*   Updated: 2023/04/07 21:39:19 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	is_text(int type)
{
	if (type == TEXT || type == DUP_QUOTES || \
	type == SING_QUOTES || type == EXTENDED_TEXT || type == EXTENDED_QUOT)
		return (1);
	return (0);
}

int	arg_checker(int type)
{
	if (!is_arg_type(type))
		return (1);
	else if (is_redir(type))
		return (1);
	else
		return (0);
}

int	check_input_so(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (0);
		i++;
	}
	return (1);
}
