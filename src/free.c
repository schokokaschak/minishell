/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:27:35 by nradin            #+#    #+#             */
/*   Updated: 2023/04/08 17:44:18 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

t_token_list	*free_tokens(t_token_list	*tokens)
{
	t_token_list	*cur;

	if (!tokens)
		return (NULL);
	cur = tokens;
	while (cur)
	{
		if (cur->type == EXTENDED_QUOT || cur->type == EXTENDED_TEXT)
			free (cur->token);
		tokens = tokens->next;
		free(cur);
		cur = tokens;
	}
	return (NULL);
}

void	free_argv(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i] != NULL)
		free(argv[i]);
	free(argv[i]);
	free(argv);
}

void	free_cmnd_in_loop(t_cmnd *command)
{
	int	i;

	i = -1;
	if (!command)
		return ;
	while (command->argv[++i] != NULL)
		free(command->argv[i]);
	free(command->argv[i]);
	free(command->argv);
	if (command->f_in)
		close(command->infile);
	if (command->f_out)
		close(command->outfile);
	if (command->here)
		unlink(".heredoc_tmp");
	i = -1;
	if (command->cp == 1)
	{
		while (command->cmd_paths[++i] != NULL)
			free(command->cmd_paths[i]);
		if (command->cmd_paths != NULL)
			free(command->cmd_paths);
	}
}

void	free_pipe_in_loop(t_pipe_groups *pipes)
{
	t_pipe_groups	*cur;

	if (!pipes)
		return ;
	cur = pipes;
	while (pipes)
	{
		pipes = pipes->next;
		free_cmnd_in_loop(cur->cmnd);
		if (cur->cmnd)
			free(cur->cmnd);
		free(cur);
		cur = pipes;
	}
}

void	free_data_in_loop(t_data *data, char *input)
{
	t_log_groups	*buf;
	t_log_groups	*cur;

	if (data->log_groups)
		free_tokens(data->log_groups->tokens);
	cur = data->log_groups;
	buf = cur;
	while (cur)
	{
		cur = cur->next;
		free_pipe_in_loop(buf->pipe_groups);
		free(buf);
		buf = cur;
	}
	if (input && *input)
		free(input);
	free(data);
}
