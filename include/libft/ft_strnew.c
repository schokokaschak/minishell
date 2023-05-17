/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:05:43 by akashets          #+#    #+#             */
/*   Updated: 2023/04/02 14:06:18 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(const int size)
{
	int		i;
	char	*new_string;

	if (size < 0)
	{
		return (0);
	}
	i = 0;
	new_string = (char *)malloc(sizeof(char) * (size + 1));
	while (i <= size)
	{
		new_string[i] = '\0';
		i++;
	}
	return (new_string);
}
