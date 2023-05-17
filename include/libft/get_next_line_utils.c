/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:56:46 by akashets          #+#    #+#             */
/*   Updated: 2023/03/26 16:38:34 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"

int	findnl(char *str)
{
	if (str)
	{
		while (*str)
		{
			if (*str == '\n')
				return (1);
			str++;
		}
	}
	return (0);
}

char	*ft_line(char *rest)
{
	int		i;
	char	*new;

	i = 0;
	if (rest[i] == '\0')
		return (NULL);
	while (rest[i] != '\n' && rest[i] != '\0')
		i++;
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (rest[i] != '\n' && rest[i] != '\0')
	{
		new[i] = rest[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_rest(char *rest)
{
	char	*new;
	int		i;
	int		k;

	i = 0;
	while (rest[i] != '\n' && rest[i] != '\0')
		i++;
	if (!rest[i] || !rest[i + 1])
	{
		free(rest);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(rest) - i + 1));
	if (new == NULL)
	{
		free(rest);
		return (NULL);
	}
	i++;
	k = 0;
	while (rest[i] != '\0')
		new[k++] = rest[i++];
	new[k] = '\0';
	free(rest);
	return (new);
}
