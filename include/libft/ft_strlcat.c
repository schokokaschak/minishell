/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:08:02 by nradin            #+#    #+#             */
/*   Updated: 2022/12/14 10:29:30 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	i;
	size_t	j;

	n = size - ft_strlen(dst) - 1;
	if (size < ft_strlen(dst) + 1)
		return (ft_strlen(src) + size);
	i = ft_strlen(dst);
	j = 0;
	while (j < n && *(src + j))
	{
		*(dst + i + j) = *(src + j);
		j++;
	}
	*(dst + i + j) = 0;
	return (ft_strlen(dst) + ft_strlen(src + j));
}
