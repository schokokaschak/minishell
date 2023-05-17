/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:17:26 by nradin            #+#    #+#             */
/*   Updated: 2023/04/09 15:17:18 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	get_exit_code(char *code)
{
	int	exit_code;
	int	i;

	i = 0;
	exit_code = 1;
	while (code[i])
	{
		if (!ft_isdigit(code[i]))
		{
			exit_code = 255;
			break ;
		}
		i++;
	}
	if (exit_code != 255)
		exit_code = ft_atoi(code);
	return (exit_code);
}

int	builtin_exit(char **argv, t_data *data)
{
	int	argc;
	int	exit_code;

	argc = get_env_size(argv);
	if (argc > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (argc == 1)
		exit_code = 0;
	else
		exit_code = get_exit_code(argv[1]);
	free_data_in_loop(data, data->input);
	free_argv(g_envp);
	clear_history();
	exit(exit_code % 256);
	return (0);
}
