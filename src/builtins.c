/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:25:05 by nradin            #+#    #+#             */
/*   Updated: 2023/04/06 16:17:44 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

char	**clone_envp(void)
{
	int		i;
	char	**new_envp;

	new_envp = ft_calloc(sizeof(char *), get_env_size(g_envp) + 1);
	i = 0;
	while (g_envp[i])
	{
		new_envp[i] = g_envp[i];
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

int	check_var_name(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	get_builtins(char *command)
{
	if (!ft_strncmp(command, "exit", 5))
		return (1);
	if (!ft_strncmp(command, "env", 4))
		return (1);
	if (!ft_strncmp(command, "pwd", 4))
		return (1);
	if (!ft_strncmp(command, "echo", 5))
		return (1);
	if (!ft_strncmp(command, "cd", 3))
		return (1);
	if (!ft_strncmp(command, "unset", 6))
		return (1);
	if (!ft_strncmp(command, "export", 7))
		return (1);
	return (0);
}

int	exec_builtins(char *command, char **argv, t_data *d)
{
	if (!ft_strncmp(command, "exit", 5))
		return (builtin_exit(argv, d));
	if (!ft_strncmp(command, "env", 4))
		return (output_env(g_envp));
	if (!ft_strncmp(command, "pwd", 4))
		return (builtin_pwd());
	if (!ft_strncmp(command, "echo", 5))
		return (builtin_echo(argv));
	if (!ft_strncmp(command, "cd", 3))
		return (builtin_cd(argv));
	if (!ft_strncmp(command, "unset", 6))
		return (builtin_unset(argv));
	if (!ft_strncmp(command, "export", 7))
		return (builtin_export(argv));
	return (-1);
}
