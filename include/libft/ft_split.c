/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nradin <nradin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 02:23:05 by nradin            #+#    #+#             */
/*   Updated: 2023/01/04 19:42:59 by nradin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	measure_words(char const *s, char c, int *word_sizes)
{
	size_t	i;
	size_t	wc;

	i = 0;
	wc = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			wc++;
			*(word_sizes + wc - 1) = 0;
			while (*(s + i) && *(s + i) != c)
			{
				(*(word_sizes + wc - 1))++;
				i++;
			}
			continue ;
		}
		i++;
	}
	return (wc);
}

static void	fill_words(char const *s, char c, int *word_sizes, char **words)
{
	size_t	i;
	size_t	j;
	size_t	wc;

	i = 0;
	wc = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			wc++;
			*(words + wc - 1) = (char *)malloc(*(word_sizes + wc - 1) + 1);
			j = 0;
			while (*(s + i) && *(s + i) != c)
			{
				*(*(words + wc - 1) + j) = *(s + i);
				i++;
				j++;
			}
			*(*(words + wc - 1) + j) = 0;
			continue ;
		}
		i++;
	}
	*(words + wc) = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	int		*word_sizes;
	char	**words;

	word_sizes = (int *)malloc((ft_strlen(s) / 2 + 1) * sizeof(int));
	word_count = measure_words(s, c, word_sizes);
	words = malloc(sizeof(char *) * (word_count + 1));
	fill_words(s, c, word_sizes, words);
	free(word_sizes);
	return (words);
}
