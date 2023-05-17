/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extensions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 11:48:21 by nradin            #+#    #+#             */
/*   Updated: 2023/04/08 17:41:24 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	extend_last_exit(t_token_list *token, int *index, int last_exit)
{
	char	*last;
	char	*ext;
	char	*temp;

	last = ft_itoa(last_exit);
	temp = token->token;
	ext = malloc(ft_strlen(temp) + ft_strlen(last) - 1);
	ft_strlcpy(ext, temp, *index + 1);
	ft_strlcpy(&ext[*index], last, ft_strlen(last) + 1);
	ft_strlcpy(&ext[*index + ft_strlen(last)], &temp[*index + 2], \
						token->len - *index - 1);
	if (token->type == EXTENDED_TEXT || token->type == EXTENDED_QUOT)
		free(temp);
	*index += ft_strlen(last) - 1;
	free(last);
	token->token = ext;
	if (token->type == TEXT || token->type == EXTENDED_TEXT)
		token->type = EXTENDED_TEXT;
	else
		token->type = EXTENDED_QUOT;
	token->len = ft_strlen(ext);
}

void	extend_variable(t_token_list *t, int *idx, int var, int val)
{
	char	*ext;
	char	*temp;
	int		var_index;

	while (*idx + var + 1 < t->len && (ft_isalnum(t->token[*idx + var + 1]) || \
			t->token[*idx + var + 1] == '_'))
		var++;
	var_index = find_variable(g_envp, &t->token[*idx + 1], var);
	if (var_index != -1)
		val = ft_strlen(g_envp[var_index] + var + 1);
	temp = t->token;
	ext = malloc(ft_strlen(temp) + val - var - 1);
	ft_strlcpy(ext, temp, *idx + 1);
	if (val)
		ft_strlcpy(&ext[*idx], g_envp[var_index] + var + 1, val + 1);
	ft_strlcpy(&ext[*idx + val], &temp[*idx + var + 1], t->len - *idx - var);
	if (t->type == EXTENDED_TEXT || t->type == EXTENDED_QUOT)
		free(temp);
	t->token = ext;
	if (t->type == TEXT || t->type == EXTENDED_TEXT)
		t->type = EXTENDED_TEXT;
	else
		t->type = EXTENDED_QUOT;
	t->len = ft_strlen(ext);
	*idx += val - 1;
}

void	extension(t_token_list *token, int *index, int last_exit)
{
	int	var;
	int	val;

	val = 0;
	var = 0;
	if (token->len <= *index + 1)
		return ;
	else if (token->token[*index + 1] == '?')
		extend_last_exit(token, index, last_exit);
	else
		extend_variable(token, index, var, val);
}

void	extension_home(t_token_list *token)
{
	int		i;
	int		add;
	char	*new;

	i = -1;
	add = 0;
	new = malloc(ft_strlen(token->token) + 4);
	while (token->token[++i])
	{
		if (add == 0 && token->token[i] == '~')
		{
			ft_strlcpy(&new[i], "$HOME", 6);
			add = 4;
			continue ;
		}
		new[i + add] = token->token[i];
	}
	new[i + add] = 0;
	if (token->type == EXTENDED_TEXT)
		free(token->token);
	token->token = new;
	token->len += 4;
	token->type = EXTENDED_TEXT;
}

int	parse_extensions(t_token_list *tokens, int *last_exit)
{
	int	i;
	int	k;

	k = *last_exit;
	while (tokens)
	{
		if (tokens->type == TEXT || tokens->type == DUP_QUOTES)
		{
			i = 0;
			while (tokens->token[i] && i < tokens->len)
			{
				if (tokens->token[i] == '~' && (tokens->type == TEXT \
					|| tokens->type == EXTENDED_TEXT))
					extension_home(tokens);
				if (tokens->token[i] == '$')
					extension(tokens, &i, k);
				i++;
			}
		}
		tokens = tokens->next;
	}
	return (1);
}
