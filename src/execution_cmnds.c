/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmnds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:48:37 by akashets          #+#    #+#             */
/*   Updated: 2023/04/02 21:55:04 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	redir_pipes(t_cmnd *c, t_pipex *p)
{
	if (c->f_in == 1 && c->f_out == 1)
		sub_dup2(c->infile, c->outfile);
	else if (c->f_in == 1 && p->ncmd != 1)
		sub_dup2(c->infile, p->pipe[2 * p->idd + 1]);
	else if (c->f_out == 1 && p->ncmd != 1)
		sub_dup2(p->pipe[2 * p->idd - 2], c->outfile);
	else if (c->f_in == 1 && p->ncmd == 1)
		sub_dup2(c->infile, 1);
	else if (c->f_out == 1 && p->ncmd == 1)
		sub_dup2(0, c->outfile);
	else if (p->ncmd == 1)
		sub_dup2(0, 1);
	else if (p->idd == p->ncmd - 1)
		sub_dup2(p->pipe[2 * p->idd - 2], 1);
	else if (p->idd == 0)
		sub_dup2(0, p->pipe[2 * p->idd + 1]);
	else
		sub_dup2(p->pipe[2 * p->idd - 2], p->pipe[2 * p->idd + 1]);
}	

void	parent_process(t_data *data, t_cmnd *c, t_pipe_groups *t)
{
	int	fd_in;
	int	fd_out;

	if (get_builtins(c->argv[0]) && !t->next && !t->prev)
	{
		fd_in = dup(STDIN_FILENO);
		fd_out = dup(STDOUT_FILENO);
		if (c->f_in == 1 && c->f_out == 1)
			sub_dup2(c->infile, c->outfile);
		else if (c->f_out == 1)
			sub_dup2(0, c->outfile);
		else if (c->f_in == 1)
			sub_dup2(c->infile, 1);
		data->last_log_ret = exec_builtins(c->argv[0], c->argv, data);
		sub_dup2(fd_in, fd_out);
		close(fd_in);
		close(fd_out);
	}
	if (!get_builtins(c->argv[0]) && !t->next)
	{
		data->flag = 1;
		data->flag_pid = c->pid;
	}
}

static void	check_command(char *cmd)
{
	if (!cmd)
	{
		perror("command not found");
		exit(127);
	}
	if (cmd[ft_strlen(cmd) - 1] == '/' || cmd[ft_strlen(cmd) - 1] == '.')
	{
		perror("Is a directory");
		exit(126);
	}
}

void	child_process(t_cmnd *c, t_pipex *p, t_pipe_groups *t, t_data *d)
{
	redir_pipes(c, p);
	if (p->ncmd > 1)
		ft_close(p);
	if (get_builtins(c->argv[0]))
	{
		if (t->next || t->prev)
			exit(exec_builtins(c->argv[0], c->argv, d));
	}
	else
	{
		c->cmd = ft_get_cmd(c->cmd_paths, c->argv[0]);
		check_command(c->cmd);
		if (execve(c->cmd, c->argv, g_envp) == -1)
		{
			perror("minishell: failed to execute\n");
			exit(EXIT_FAILURE);
		}
	}
	exit (0);
}

void	start_the_show(t_cmnd *c, t_pipex p, t_data *d, t_pipe_groups *t)
{
	c->pid = fork();
	child_sig();
	if (c->pid == 0)
		child_process(c, &p, t, d);
	else
		parent_process(d, c, t);
}
