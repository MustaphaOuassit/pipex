/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:35:22 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/03 10:49:20 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_separator(char str, char c)
{
	return (str != c && str != '\n' && str != '\t');
}

int	ft_count_words(char *str, char c)
{
	int		i;
	int		in_word;
	int		count;

	i = 0;
	in_word = 0;
	count = 0;
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str == c || *str == '\n' || *str == '\t')
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

int	ft_word_length(char *str, int i, char c)
{
	int		length;

	length = 0;
	while (ft_separator(str[i], c) && str[i] != '\0')
	{
		length++;
		i++;
	}
	return (length);
}

void	*fr_ee(char **words, int j)
{
	while (j)
		free(words[j--]);
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	words = (char **)malloc(sizeof(char *)
			* (ft_count_words((char *)s, c) + 1));
	if (!words || !s)
		return (0);
	while (s[i] != '\0' && j < ft_count_words((char *)s, c))
	{
		k = 0;
		i = skip(i, s, c);
		words[j] = (char *)malloc(sizeof(char)
				* ft_word_length((char *)s, i, c) + 1);
		if (!words[j])
			return (fr_ee(words, j));
		while (ft_separator(s[i], c) && s[i] != '\0')
			words[j][k++] = s[i++];
		words[j++][k] = '\0';
	}
	words[j] = 0;
	return (words);
}
