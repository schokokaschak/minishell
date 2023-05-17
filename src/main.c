/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:33:18 by akashets          #+#    #+#             */
/*   Updated: 2023/04/07 21:29:59 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

static int	get_bs_size(char *buf)
{
	int	i;
	int	k;
	int	y;

	k = 0;
	y = 0;
	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\'')
			y = !y;
		if (buf[i] == '\\' && !y)
			i++;
		if (buf[i] == '\0')
			return (k);
		k++;
		i++;
	}
	return (k);
}

static char	*check_bs(char *buf)
{
	char	*new;
	int		i;
	int		k;
	int		y;

	i = get_bs_size(buf);
	new = malloc(sizeof(char) * (i + 1));
	k = 0;
	y = 0;
	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\'')
			y = !y;
		if (buf[i] == '\\' && !y)
			i++;
		if (buf[i] == '\0')
			break ;
		new[k] = buf[i];
		k++;
		i++;
	}
	new[k] = '\0';
	return (new);
}

static char	*read_input(void)
{
	char	*buf;
	char	*ret;

	ret = NULL;
	buf = readline("minishell : ");
	if (buf)
	{
		if (*buf)
			add_history(buf);
		ret = check_bs(buf);
		free(buf);
	}
	return (ret);
}

static void	mini_shell(int last_exit)
{
	char			*input;
	t_token_list	*tokens;
	t_data			*data;

	while (1)
	{
		input = read_input();
		if (!input)
			exit(ctrl_d_exit());
		if (check_input_so(input))
			continue ;
		tokens = lexer(input);
		if (!tokens)
		{
			last_exit = 2;
			continue ;
		}
		data = parse(&tokens, &last_exit, input);
		if (!data)
			continue ;
		data->input = input;
		execution(data, data->log_groups, 0);
		last_exit = data->last_log_ret;
		free_data_in_loop(data, data->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	last_exit;

	last_exit = 0;
	(void)argc;
	(void)argv;
	g_envp = get_envp(envp);
	signals();
	mini_shell(last_exit);
	return (0);
}
