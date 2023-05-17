/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:09:41 by akashets          #+#    #+#             */
/*   Updated: 2023/04/02 14:09:44 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*cpy;

	if (ft_strlen((char *)s1) < n)
		cpy = ft_strnew(ft_strlen((char *)s1));
	else
		cpy = ft_strnew(n);
	if (cpy == NULL)
		return (NULL);
	return (ft_strncpy(cpy, (char *)s1, n));
}
