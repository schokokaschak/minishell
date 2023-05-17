/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 16:29:10 by akashets          #+#    #+#             */
/*   Updated: 2023/04/02 20:32:05 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	sub_heredoc(char *limit, int file)
{
	char	*line;
	char	*ret1;
	char	*ret2;

	ret1 = NULL;
	ret2 = NULL;
	while (1)
	{
		heredoc_sig();
		line = readline("here_doc> ");
		if (strcmp(line, limit) == 0)
		{
			write(file, ret1, ft_strlen(ret1));
			free(ret1);
			free(line);
			close(file);
			exit(1);
		}
		ret2 = ft_strjoin(ret1, line);
		free(ret1);
		ret1 = ft_strjoin(ret2, "\n");
		free(ret2);
		free(line);
	}
}

void	here_doc(char *limit, int fd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		sub_heredoc(limit, fd);
	else
		waitpid(pid, NULL, 0);
	signals();
}
