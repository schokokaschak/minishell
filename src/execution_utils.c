/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:26:03 by akashets          #+#    #+#             */
/*   Updated: 2023/04/09 14:41:01 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

char	*find_path(char **envp, t_pipex *pipex)
{
	int	i;

	(void)pipex;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*ft_get_cmd(char **paths, char *cmd)
{
	char	*buf;
	char	*com;
	int		i;

	i = 0;
	if (!ft_strncmp(cmd, "/", 1) || !ft_strncmp(cmd, "./", 2))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		else
			return (0);
	}
	if (paths == NULL)
		return (0);
	while (paths[i])
	{
		buf = ft_strjoin(paths[i], "/");
		com = ft_strjoin(buf, cmd);
		free(buf);
		if (access(com, F_OK | X_OK) == 0)
			return (com);
		free(com);
		i++;
	}
	return (0);
}

void	sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

int	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->ncmd - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
		{
			printf("Problem with pipes\n");
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_close(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->pipe)
	{
		while (i < (pipex->pipe_n))
		{
			close(pipex->pipe[i]);
			i++;
		}
	}
}
