/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:50:03 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/01 09:25:41 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char*s, int c);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
char    *get_path(char **envp, char *cmd);
int     ft_strncmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);

#endif