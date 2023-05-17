/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:03:37 by nradin            #+#    #+#             */
/*   Updated: 2023/04/01 16:09:37 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

char	**delete_variable(int index)
{
	int		i;
	int		offset;
	char	**new_envp;

	new_envp = ft_calloc(sizeof(char *), get_env_size(g_envp));
	i = -1;
	offset = 0;
	while (g_envp[++i])
	{
		if (i == index)
			offset++;
		else
			new_envp[i - offset] = ft_strdup(g_envp[i]);
		free(g_envp[i]);
	}
	new_envp[i - offset] = NULL;
	free(g_envp);
	return (new_envp);
}

int	builtin_unset(char **argv)
{
	int	i;
	int	index;

	i = 0;
	while (argv[++i])
	{
		index = find_variable(g_envp, argv[i], ft_strlen(argv[i]));
		if (index < 0)
			continue ;
		g_envp = delete_variable(index);
	}
	return (0);
}
