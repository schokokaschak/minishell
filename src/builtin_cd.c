/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:17:26 by nradin            #+#    #+#             */
/*   Updated: 2023/04/06 12:55:15 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	set_new_pwd(void)
{
	char	*old_path;
	char	*path_var;
	char	path[256];
	int		index1;
	int		index2;

	getcwd(path, sizeof(path));
	index1 = find_variable(g_envp, "OLDPWD", 6);
	if (index1 >= 0)
		g_envp = delete_variable(index1);
	index2 = find_variable(g_envp, "PWD", 3);
	if (index2 >= 0)
	{
		old_path = g_envp[index2];
		old_path = ft_strjoin("OLD", old_path);
		g_envp = add_variable(old_path, index1);
		free(old_path);
		path_var = ft_strjoin("PWD=", path);
		g_envp = delete_variable(index2);
		g_envp = add_variable(path_var, index2);
		free(path_var);
	}
}

char	*get_path(char *arg)
{
	char	*path;
	int		i;

	if (arg == NULL)
	{
		i = find_variable(g_envp, "HOME", 4);
		if (i < 0)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (NULL);
		}
		path = g_envp[i] + 5;
	}
	else
		path = arg;
	return (path);
}

int	builtin_cd(char	**argv)
{
	char	*path;

	if (get_env_size(argv) > 2)
	{
		ft_putstr_fd("cd: string not in pwd\n", 2);
		return (1);
	}
	else
	{
		path = get_path(argv[1]);
		if (!path)
			return (-1);
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: no such file or directory\n", 2);
		return (1);
	}
	set_new_pwd();
	return (0);
}
