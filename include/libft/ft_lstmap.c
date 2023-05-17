/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:52:25 by nradin            #+#    #+#             */
/*   Updated: 2022/11/13 17:33:33 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*cur_old;
	t_list	*cur_new;

	if (lst == NULL)
		return (NULL);
	cur_old = lst;
	new = ft_lstnew(f((*cur_old).content));
	cur_new = new;
	cur_old = (*cur_old).next;
	while (cur_old != NULL)
	{
		(*cur_new).next = ft_lstnew(f((*cur_old).content));
		if ((*cur_new).next == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		cur_new = (*cur_new).next;
		cur_old = (*cur_old).next;
	}
	return (new);
}
