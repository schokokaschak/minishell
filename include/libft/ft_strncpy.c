/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:12:04 by akashets          #+#    #+#             */
/*   Updated: 2023/04/02 14:12:07 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t		index;
	size_t		src_len;

	src_len = ft_strlen(src);
	index = 0;
	while (index < len)
	{
		if (index <= src_len)
			dest[index] = src[index];
		else
			dest[index] = '\0';
		index++;
	}
	return (dest);
}
