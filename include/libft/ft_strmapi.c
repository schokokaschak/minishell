/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:52:22 by nradin            #+#    #+#             */
/*   Updated: 2022/11/16 14:14:26 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	res = (char *)malloc(ft_strlen(s) + 1);
	i = 0;
	while (*(s + i))
	{
		*(res + i) = f(i, *(s + i));
		i++;
	}
	*(res + i) = 0;
	return (res);
}
