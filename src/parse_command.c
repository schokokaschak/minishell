/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:06:40 by akashets          #+#    #+#             */
/*   Updated: 2023/04/07 21:39:43 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

char	**free_temp(char *temp_arg, char *temp_parse)
{
	if (temp_arg != NULL)
		free(temp_arg);
	if (temp_parse != NULL)
		free(temp_parse);
	return (NULL);
}

char	**create_args(t_token_list **token, int k, char **argv, int i)
{
	char			*temp_arg;
	char			*temp_parse;
	t_token_list	*cur;

	cur = *token;
	while (--k > 0 && cur)
	{
		if (cur && k > 0 && (is_text(cur->type) || is_redir(cur->type)))
		{
			if (cur->prev == NULL || arg_checker(cur->prev->type))
				argv[++i] = parse_str(&cur);
			else
			{
				temp_parse = parse_str(&cur);
				if (temp_parse == NULL)
					return (free_temp(temp_arg, temp_parse));
				temp_arg = argv[i];
				argv[i] = ft_strjoin(temp_arg, temp_parse);
				free_temp(temp_arg, temp_parse);
			}
		}
		cur = cur->next;
	}
	argv[++i] = NULL;
	return (argv);
}

char	**create_args_2(char **argv, int k, int y)
{
	int		i;
	char	**new;

	i = get_size_argv(argv, y);
	if (i == 0)
	{
		free_argv(argv);
		return (NULL);
	}
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (argv[i] != NULL)
	{
		if (check_jump(argv[i], &y, &i))
			continue ;
		new[k++] = ft_strdup(argv[i++]);
	}
	new[k] = NULL;
	free_argv(argv);
	return (new);
}

t_cmnd	*create_cmnd(t_token_list **token, int k, int *d, int y)
{
	t_cmnd			*new;
	t_token_list	*cur;
	char			**buf;
	char			**argv;

	new = malloc(sizeof(t_cmnd));
	if (new == NULL)
		return (NULL);
	cur = *token;
	y = get_arg_size(&cur, k);
	argv = malloc(sizeof(char *) * (y + 1));
	if (argv == NULL)
		return (NULL);
	y = -1;
	buf = create_args(&cur, k + 1, argv, y);
	check_fd(new, buf, d);
	y = 0;
	new->argv = create_args_2(buf, y, k + 1);
	new->cp = 0;
	if (new->argv == NULL)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

int	init_commands(t_data *new, int *last_exit)
{
	t_log_groups	*cur;
	t_pipe_groups	*buf;
	int				y;

	y = 0;
	cur = new->log_groups;
	while (cur)
	{
		buf = cur->pipe_groups;
		while (buf)
		{
			buf->cmnd = create_cmnd(&buf->tokens, \
						buf->token_count, last_exit, y);
			if (buf->cmnd == NULL)
				return (-1);
			else
				buf->cmnd->is_d = 0;
			buf = buf->next;
		}
		cur = cur->next;
	}
	return (1);
}
