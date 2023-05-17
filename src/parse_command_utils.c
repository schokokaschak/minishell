/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:46:02 by akashets          #+#    #+#             */
/*   Updated: 2023/04/07 21:30:53 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

char	*parse_str(t_token_list **tokens)
{
	t_token_list	*worker;
	char			*command;

	worker = *tokens;
	if (worker->type == DUP_QUOTES || worker->type == EXTENDED_QUOT)
		command = get_command(worker->token, '\"');
	else if (worker->type == SING_QUOTES)
		command = get_command(worker->token, '\'');
	else if (is_redir(worker->type))
		command = get_command_fd(worker->token);
	else
		command = get_command_sp(worker->token, ' ');
	return (command);
}

int	is_arg_type(int type)
{
	if (type == DUP_QUOTES)
		return (1);
	if (type == SING_QUOTES)
		return (1);
	if (type == TEXT)
		return (1);
	if (type == EXTENDED_QUOT)
		return (1);
	if (type == EXTENDED_TEXT)
		return (1);
	if (is_redir(type))
		return (1);
	return (0);
}

int	get_arg_size(t_token_list **token, int k)
{
	int				i;
	t_token_list	*worker;

	worker = *token;
	i = 0;
	while (worker && k > 0)
	{
		if (worker->prev == NULL || !is_log_group(worker->type))
			if (is_arg_type(worker->type))
				i++;
		worker = worker->next;
	}
	return (i);
}

int	ft_argv_cmp(char *argv)
{
	if (!ft_strncmp(argv, ">>", 2))
		return (1);
	if (!ft_strncmp(argv, ">", 1))
		return (1);
	if (!ft_strncmp(argv, "<<", 2))
		return (1);
	if (!ft_strncmp(argv, "<", 1))
		return (1);
	return (0);
}

int	get_size_argv(char **argv, int y)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (argv[i] != NULL)
	{
		if (ft_argv_cmp(argv[i]))
		{
			i += 2;
			y -= 2;
			continue ;
		}
		if (check_types(argv[i], y))
		{
			i++;
			y -= 1;
			continue ;
		}
		i++;
		k++;
		y--;
	}
	return (k);
}
