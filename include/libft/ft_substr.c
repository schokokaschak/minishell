/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:30:26 by nradin            #+#    #+#             */
/*   Updated: 2022/12/13 19:27:07 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (len < ft_strlen(s + start))
		sub = (char *)malloc(len + 1);
	else
		sub = (char *)malloc(ft_strlen(s + start) + 1);
	if (sub == NULL)
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (*(s + start + i) && i < len)
		{
			*(sub + i) = *(s + start + i);
			i++;
		}
	}
	*(sub + i) = 0;
	return (sub);
}
