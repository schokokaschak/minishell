/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:50:13 by akashets          #+#    #+#             */
/*   Updated: 2023/03/26 16:38:43 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"

int	ft_free(char *str)
{
	if (str)
		free(str);
	return (-1);
}

char	*str_join(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	if (s1)
		while (s1[++i])
			str[i] = s1[i];
	else
		i = 0;
	if (s2)
		while (s2[++j])
			str[i + j] = s2[j];
	else
		j = 0;
	str[i + j] = '\0';
	if (s1)
		free(s1);
	return (str);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*rest;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (ft_free(rest));
	i = 1;
	while (!findnl(rest) && i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i < 0)
			return (ft_free(buf));
		buf[i] = '\0';
		rest = str_join(rest, buf);
	}
	free(buf);
	*line = ft_line(rest);
	rest = ft_rest(rest);
	if (!rest && i == 0)
		return (0);
	return (1);
}
