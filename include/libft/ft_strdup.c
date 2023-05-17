/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:04:14 by nradin            #+#    #+#             */
/*   Updated: 2023/03/28 18:57:49 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	size_t	i;
	char	*d;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	d = (char *)malloc(size + 1);
	if (!d)
		return (NULL);
	i = 0;
	while (*(s + i))
	{
		*(d + i) = *(s + i);
		i++;
	}
	*(d + i) = 0;
	return (d);
}
