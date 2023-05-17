/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:01:59 by nradin            #+#    #+#             */
/*   Updated: 2022/12/29 17:10:15 by nradin           ###   ########.fr       */
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

static void	ft_itoa_no_malloc(int n, char *nbr)
{
	int		i;
	long	n_long;
	int		size;

	size = count_size(n);
	i = size - 1;
	n_long = n;
	if (n_long == 0)
		*nbr = '0';
	if (n_long < 0)
	{
		*nbr = '-';
		n_long = -n_long;
	}
	while (n_long != 0)
	{
		*(nbr + i) = n_long % 10 + 48;
		n_long /= 10;
		i--;
	}
	*(nbr + size) = 0;
}

void	ft_putnbr_fd(int n, int fd)
{
	char	nbr[12];

	ft_itoa_no_malloc(n, nbr);
	write(fd, nbr, ft_strlen(nbr));
}
