/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:54:39 by akashets          #+#    #+#             */
/*   Updated: 2023/04/09 14:47:58 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	get_pipes_count(t_pipe_groups **pipe_groups)
{
	t_pipe_groups	*worker;
	int				i;

	worker = *pipe_groups;
	i = 0;
	while (worker)
	{
		i++;
		worker = worker->next;
	}
	return (i);
}

void	sub_exec(t_pipe_groups **pipe_groups, t_data *d, t_pipex p)
{
	t_pipe_groups	*worker;

	worker = *pipe_groups;
	p.idd = -1;
	while (worker)
	{
		if (p.paths == NULL)
			worker->cmnd->cmd_paths = NULL;
		else
		{
			worker->cmnd->cmd_paths = ft_split(p.paths + 5, ':');
			worker->cmnd->cp = 1;
		}
		++p.idd;
		start_the_show(worker->cmnd, p, d, worker);
		worker = worker->next;
	}
}

int	init_pipes(t_pipex *pipex)
{
	pipex->pipe_n = 2 * (pipex->ncmd - 1);
	pipex->pipe = malloc(sizeof(int) * pipex->pipe_n);
	if (!pipex->pipe)
	{
		printf("Error pipes\n");
		return (0);
	}
	if (!create_pipes(pipex))
	{
		printf("Error pipes\n");
		return (0);
	}
	return (1);
}

int	execute_pipes(t_pipe_groups **pipe_groups, t_data *d)
{
	t_pipex			pipex;
	int				status;

	pipex.ncmd = get_pipes_count(pipe_groups);
	if (pipex.ncmd > 1 && !init_pipes(&pipex))
		return (0);
	pipex.paths = find_path(g_envp, &pipex);
	sub_exec(pipe_groups, d, pipex);
	if (pipex.ncmd > 1)
		ft_close(&pipex);
	if (d->flag)
	{
		waitpid(d->flag_pid, &status, 0);
		if (WIFEXITED(status))
			d->last_log_ret = WEXITSTATUS(status);
	}
	while (wait(NULL) > 0)
		continue ;
	signals();
	if (pipex.ncmd > 1)
		free(pipex.pipe);
	return (1);
}
