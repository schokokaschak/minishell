/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:06:40 by akashets          #+#    #+#             */
/*   Updated: 2023/04/07 21:20:49 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	ft_app_outfile(t_cmnd *command, char **argv, int y, int *d)
{
	y++;
	command->outfile = open(argv[y], O_WRONLY | O_CREAT | O_APPEND, 0000644);
	if (command->outfile < 0)
	{
		perror("Error outfile");
		*d = 2;
		return ;
	}
	command->f_out = 1;
}

void	ft_outfile(t_cmnd *command, char **argv, int y, int *d)
{
	y++;
	command->outfile = open(argv[y], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (command->outfile < 0)
	{
		perror("Error outfile");
		*d = 2;
		return ;
	}
	command->f_out = 1;
}

void	ft_heredoc(t_cmnd *command, char **argv, int y, int *d)
{
	int	fd;

	y++;
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY, 0777);
	if (fd < 0)
	{
		perror("ERR_HEREDOC");
		*d = 2;
		return ;
	}
	here_doc(argv[y], fd);
	command->infile = open(".heredoc_tmp", O_RDONLY);
	if (command->infile < 0)
	{
		*d = 2;
		unlink(".heredoc_tmp");
		perror("ERR_HEREDOC");
		return ;
	}
	command->f_in = 1;
	command->here = 1;
}

void	ft_infile(t_cmnd *command, char **argv, int y, int *d)
{
	y++;
	command->infile = open(argv[y], O_RDONLY);
	if (command->infile == -1)
	{
		perror("infile dont exists");
		*d = 2;
		return ;
	}
	command->f_in = 1;
}

void	check_fd(t_cmnd *command, char **argv, int *d)
{
	int	i;

	i = 0;
	command->f_in = 0;
	command->f_out = 0;
	command->here = 0;
	while (argv[i] != NULL)
	{
		if (!ft_strncmp(argv[i], ">>", 2))
			ft_app_outfile(command, argv, i, d);
		else if (!ft_strncmp(argv[i], ">", 1))
			ft_outfile(command, argv, i, d);
		else if (!ft_strncmp(argv[i], "<<", 2))
			ft_heredoc(command, argv, i, d);
		else if (!ft_strncmp(argv[i], "<", 1))
			ft_infile(command, argv, i, d);
		i++;
	}
}
