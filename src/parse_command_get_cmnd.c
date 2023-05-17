/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_get_cmnd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:43:49 by akashets          #+#    #+#             */
/*   Updated: 2023/04/07 21:30:13 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

char	*get_command(char *str, char ok)
{
	int		i;
	char	*cmd;

	i = 0;
	while (str[i] != ok && !(ok == ' ' && (ft_isspace(str[i]) || \
				str[i] == '\'' || str[i] == '\"')) && str[i] != '\0')
		i++;
	cmd = malloc(sizeof(char) * (i + 1));
	if (cmd == NULL)
		return (NULL);
	i = 0;
	while (str[i] != ok && !(ok == ' ' && (ft_isspace(str[i]) || \
				str[i] == '\'' || str[i] == '\"')) && str[i] != '\0')
	{
		cmd[i] = str[i];
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

char	*get_command_sp(char *str, char ok)
{
	int		i;
	char	*cmd;

	i = 0;
	while (str[i] != ok && str[i] != 38 && str[i] != 124 && str[i] != 40 && \
			str[i] != 41 && !(ok == ' ' && (ft_isspace(str[i]) || \
				str[i] == '\'' || str[i] == '\"')) && str[i] != '\0')
		i++;
	cmd = malloc(sizeof(char) * (i + 1));
	if (cmd == NULL)
		return (NULL);
	i = 0;
	while (str[i] != ok && str[i] != 38 && str[i] != 124 && str[i] != 40 && \
			str[i] != 41 && !(ok == ' ' && (ft_isspace(str[i]) || \
				str[i] == '\'' || str[i] == '\"')) && str[i] != '\0')
	{
		cmd[i] = str[i];
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

char	*get_command_fd(char *str)
{
	int		i;
	char	*cmd;

	i = 0;
	while (str[i] == 62 || str[i] == 60)
		i++;
	cmd = malloc(sizeof(char) * (i + 1));
	if (cmd == NULL)
		return (NULL);
	i = 0;
	while (str[i] == 62 || str[i] == 60)
	{
		cmd[i] = str[i];
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

int	check_jump(char *argv, int *y, int *i)
{
	if (ft_argv_cmp(argv))
	{
		*i += 2;
		*y -= 2;
		return (1);
	}
	if (argv != NULL && check_types(argv, --(*y)))
	{
		*i += 1;
		return (1);
	}
	return (0);
}
