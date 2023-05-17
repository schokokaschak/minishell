/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:17:26 by nradin            #+#    #+#             */
/*   Updated: 2023/04/09 14:37:26 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	find_min_str(int size, char **envp)
{
	int		min;
	int		j;

	min = 0;
	j = 0;
	while (++j < size)
	{
		if (!envp[min])
		{
			min++;
			continue ;
		}
		if (envp[j] && ft_strncmp(envp[j], envp[min], \
			ft_strlen(envp[j]) + ft_strlen(envp[min])) < 0)
			min = j;
	}
	return (min);
}

void	print_export(void)
{
	int		i;
	int		size;
	int		min;
	char	**envp;

	i = 0;
	size = get_env_size(g_envp);
	envp = clone_envp();
	while (i < size)
	{
		min = find_min_str(size, envp);
		write(1, "declare -x ", 11);
		write(1, envp[min], ft_strchr(envp[min], '=') - envp[min]);
		write(1, "\"", 1);
		write(1, ft_strchr(envp[min], '='), \
			ft_strlen(ft_strchr(envp[min], '=') + 1));
		write(1, "\"\n", 2);
		envp[min] = NULL;
		i++;
	}
	free(envp);
}

char	**add_variable(char *var, int index)
{
	int		size;
	int		i;
	int		offset;
	char	**new_envp;

	size = get_env_size(g_envp);
	new_envp = ft_calloc(sizeof(char *), size + 2);
	i = 0;
	offset = 0;
	while (g_envp[i] || !offset)
	{
		if (i == index && !offset)
		{
			new_envp[i] = ft_strdup(var);
			offset = 1;
			continue ;
		}
		else
			new_envp[i + offset] = g_envp[i];
		i++;
	}
	new_envp[i + offset] = NULL;
	free(g_envp);
	return (new_envp);
}

void	update_variable(int index, char *arg)
{
	if (index > 0)
	{
		g_envp = delete_variable(index);
		g_envp = add_variable(arg, index);
	}
	else
		g_envp = add_variable(arg, get_env_size(g_envp));
}

int	builtin_export(char **argv)
{
	int	i;
	int	index;

	if (!argv[1])
	{
		print_export();
		return (0);
	}
	i = 0;
	while (argv[++i])
	{
		if (!ft_strchr(argv[i], '='))
			continue ;
		else if (!check_var_name(argv[i]))
			ft_putstr_fd("export: not valid in this context\n", 2);
		index = find_variable(g_envp, argv[i], ft_strchr(argv[i], '=') \
															- argv[i]);
		update_variable(index, argv[i]);
	}
	return (0);
}
