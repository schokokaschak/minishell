/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:26:31 by nradin            #+#    #+#             */
/*   Updated: 2022/12/13 17:59:50 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	size;

	size = ft_strlen(s);
	i = size;
	while (i <= size)
	{
		if (*((char *)s + i) == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
