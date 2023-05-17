/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:37:11 by nradin            #+#    #+#             */
/*   Updated: 2022/12/29 16:48:23 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_present(char const chr, char const *set)
{
	size_t	i;

	i = 0;
	while (*(set + i))
	{
		if (*(set + i) == chr)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	n1;
	size_t	n2;
	char	*s2;

	n1 = 0;
	while (*(s1 + n1) && is_present(*(s1 + n1), set))
		n1++;
	if (!(*(s1 + n1)))
	{
		s2 = malloc(1);
		*s2 = 0;
		return (s2);
	}
	n2 = ft_strlen(s1) - 1;
	while (is_present(*(s1 + n2), set))
		n2--;
	s2 = ft_substr(s1, n1, n2 - n1 + 1);
	return (s2);
}
