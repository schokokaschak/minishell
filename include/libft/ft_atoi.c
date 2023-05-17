/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 15:33:54 by nradin            #+#    #+#             */
/*   Updated: 2022/10/29 16:06:13 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		s;
	long	num;

	i = 0;
	s = 1;
	num = 0;
	while (*(nptr + i) == '\f' || *(nptr + i) == '\n' || *(nptr + i) == '\r'
		|| *(nptr + i) == '\t' || *(nptr + i) == '\v' || *(nptr + i) == ' ')
		i++;
	if (*(nptr + i) == '+' || *(nptr + i) == '-')
	{
		if (*(nptr + i) == '-')
			s = -1;
		i++;
	}
	while (ft_isdigit(*(nptr + i)))
	{
		num = num * 10 + (*(nptr + i) - 48);
		i++;
	}
	return ((int)(num * s));
}
