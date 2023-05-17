/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 12:42:07 by nradin            #+#    #+#             */
/*   Updated: 2023/04/08 17:54:36 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

int	check_file_wildcard(char *dir_entry, t_wildcard *wildcard, \
									int ending, int starting)
{
	int				i;

	i = 0;
	wildcard->iter = wildcard->comps;
	while (wildcard->iter && dir_entry[i])
	{
		if (!wildcard->iter->next && !wildcard->ending)
		{
			i = ft_strlen(dir_entry) - ft_strlen(wildcard->iter->str);
			ending = 1;
		}
		if (i >= 0 && (!ft_strncmp(&dir_entry[i], \
			wildcard->iter->str, ft_strlen(wildcard->iter->str))))
		{
			i += ft_strlen(wildcard->iter->str) - 1;
			starting = 0;
			wildcard->iter = wildcard->iter->next;
		}
		else if ((starting && !wildcard->starting) || ending)
			return (0);
		i++;
	}
	if (!wildcard->iter)
		return (1);
	return (0);
}

t_wildcard	*create_wildcard(t_token_list *token, t_wildcard *wildcard)
{
	t_string_list	*cur_wild;
	int				i;
	int				j;
	int				wild;
	t_token_list	*cur;

	init_wildcard_vars(&i, &j, &wild, &cur_wild);
	check_start_end(token, wildcard);
	cur = token;
	wildcard->comps = cur_wild;
	while (cur && is_text(cur->type))
	{
		if (check_token_ends(&i, &wild, &cur_wild->str[j], &cur))
			continue ;
		add_wild_comp(&j, &wild, &cur_wild);
		cur_wild->str[j] = cur->token[i];
		j++;
		i++;
		wild = 0;
	}
	cur_wild->str[j] = 0;
	return (wildcard);
}

t_string_list	*wildcard_token(t_token_list *token)
{
	DIR				*dir;
	t_dirent		*dir_entry;
	t_string_list	*files;
	t_wildcard		*wildcard;

	files = NULL;
	wildcard = ft_calloc(sizeof(t_wildcard), 1);
	wildcard = create_wildcard(token, wildcard);
	dir = opendir(".");
	dir_entry = readdir(dir);
	while (dir_entry)
	{
		if (check_file_wildcard(dir_entry->d_name, wildcard, 0, 1))
			add_str_list(&files, dir_entry->d_name);
		dir_entry = readdir(dir);
	}
	free_str_list(wildcard->comps);
	free(wildcard);
	return (files);
}

t_token_list	*rewrite_tokens(t_token_list *token, t_string_list *files)
{
	t_token_list	*next;
	t_token_list	*prev;

	prev = token->prev;
	while (token && is_text(token->type))
	{
		next = token->next;
		free_token(token);
		token = next;
	}
	next = token;
	if (prev)
		prev->next = NULL;
	while (files)
	{
		add_token(&prev, create_token(EXTENDED_TEXT, files->str, \
						ft_strlen(files->str)));
		add_token(&prev, create_token(SPACE, " ", 1));
		files = files->next;
	}
	while (prev->next)
		prev = prev->next;
	prev->next = next;
	return (prev);
}

int	extend_wildcards(t_token_list *tokens)
{
	t_token_list	*cur;
	t_string_list	*files;

	cur = tokens;
	files = NULL;
	while (cur)
	{
		if (ft_strnchr(cur->token, '*', cur->len) && (cur->type == TEXT \
										|| cur->type == EXTENDED_TEXT))
		{
			while (cur->prev && is_text(cur->prev->type))
				cur = cur->prev;
			files = wildcard_token(cur);
			if (!files)
			{
				perror("no such file or directory");
				return (-1);
			}
			cur = rewrite_tokens(cur, files);
			free(files);
		}
		cur = cur->next;
	}
	return (1);
}
