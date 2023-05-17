/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:58:51 by nradin            #+#    #+#             */
/*   Updated: 2023/03/29 18:14:19 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/minishell.h"

void	add_str_list(t_string_list	**strings, char	*str)
{
	t_string_list	*new;
	t_string_list	*cur;

	new = malloc(sizeof(t_string_list));
	new->str = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	if (!(*strings))
		*strings = new;
	else
	{
		cur = *strings;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
		new->prev = cur;
	}
}

void	free_str_list(t_string_list	*strings)
{
	t_string_list	*prev;

	prev = NULL;
	while (strings)
	{
		if (prev)
		{
			free(prev->str);
			free(prev);
		}
		prev = strings;
		strings = strings->next;
	}
	if (prev)
	{
		free(prev->str);
		free(prev);
	}
}
