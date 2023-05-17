/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:17:26 by nradin            #+#    #+#             */
/*   Updated: 2023/04/09 14:36:10 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	echo_putstr_fd(char *out, int fd)
{
	int	i;

	i = 0;
	while (out[i])
	{
		if (out[i] == '\\')
			i++;
		write(fd, &out[i], 1);
		i++;
	}
}

int	check_echo_option(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(char **argv)
{
	int	i;
	int	no_nl;

	no_nl = 0;
	i = 1;
	if (!argv[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	while (argv[i] && check_echo_option(argv[i]))
	{
		no_nl = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!no_nl)
		ft_putstr_fd("\n", 1);
	return (0);
}
