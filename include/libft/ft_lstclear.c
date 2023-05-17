/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:02:15 by nradin            #+#    #+#             */
/*   Updated: 2022/11/13 16:08:22 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;
	t_list	*prev;

	if (lst == NULL)
		return ;
	cur = *lst;
	while (cur != NULL)
	{
		prev = cur;
		cur = (*cur).next;
		del((*prev).content);
		free(prev);
	}
	*lst = NULL;
}
