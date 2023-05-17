/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 19:45:14 by nradin            #+#    #+#             */
/*   Updated: 2022/12/29 11:54:11 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		i;
	long	n_long;
	int		size;
	char	*res;

	size = count_size(n);
	res = (char *)malloc(size + 1);
	i = size - 1;
	n_long = n;
	if (n_long == 0)
		*res = '0';
	else if (n_long < 0)
	{
		*res = '-';
		n_long = -n_long;
	}
	while (n_long != 0)
	{
		*(res + i) = n_long % 10 + 48;
		n_long /= 10;
		i--;
	}
	*(res + size) = 0;
	return (res);
}
