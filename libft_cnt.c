/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_cnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 11:59:53 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/09 11:02:56 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_stwo(char *ret, char const *s2, int ls1)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		*(ret + i + ls1) = *(s2 + i);
		i++;
	}
	*(ret + i + ls1) = '\0';
	return (ret);
}

int	size(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		ls1;
	int		ls2;
	int		i;

	if ((s1 == 0) || (s2 == 0))
		return (0);
	ls1 = size((char *)s1);
	ls2 = size((char *)s2);
	i = 0;
	ret = malloc(sizeof(char) * (ls1 + ls2 + 1));
	if (NULL == ret)
		return (0);
	while (s1[i])
	{
		*(ret + i) = *(s1 + i);
		i++;
	}
	ret = ft_stwo(ret, s2, ls1);
	return (ret);
}

char	*ft_check_file(int fd_inp, int fd_out, char *str1, char *str2)
{
	if(fd_inp < 0)
		return(str1);
	if(fd_out < 0)
		return(str2);
	return(NULL);
}
