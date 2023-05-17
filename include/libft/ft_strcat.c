/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:10:51 by akashets          #+#    #+#             */
/*   Updated: 2023/04/02 14:11:02 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int		index;
	size_t	i;

	index = ft_strlen(s1);
	i = 0;
	while (i < ft_strlen((char *)s2))
	{
		s1[index] = s2[i];
		i++;
		index++;
	}
	s1[index] = '\0';
	return (s1);
}
