/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:17:26 by akashets          #+#    #+#             */
/*   Updated: 2023/04/01 16:08:49 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	get_env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	output_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (-1);
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (1);
}

int	find_variable(char **envp, char *var, int var_size)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, var_size))
			if (envp[i] && envp[i][var_size] == '=')
				return (i);
		i++;
	}
	return (-1);
}

char	*inc_shell_lvl(char *line)
{
	char	*res;
	char	*lvl;
	int		level;

	line = &line[6];
	level = ft_atoi(line);
	level++;
	lvl = ft_itoa(level);
	res = ft_strjoin("SHLVL=", lvl);
	free(lvl);
	return (res);
}

char	**get_envp(char **envp)
{
	int		env_size;
	char	**env_copy;
	int		i;

	env_size = get_env_size(envp);
	env_copy = ft_calloc(env_size + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("SHLVL", envp[i], 5) == 0)
			env_copy[i] = inc_shell_lvl(envp[i]);
		else
			env_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}
