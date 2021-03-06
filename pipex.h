/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:50:03 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/13 09:57:42 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_fd{
	int	inp;
	int	out;
	int	*pipe;
}	t_fd;

int		get_next_line(int fd, char **line);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char*s, int c);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
char	*get_path(char **envp, char *cmd);
int		ft_strncmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
int		skip(int i, char const *s, int c);
void	*fr_ee(char **words, int j);
void	free_two(char **table);
void	first_child(char *argv, char *name_file, char **envp, t_fd fd);
void	second_child(char *argv, char *name_file, char **envp, t_fd fd);
char	*ft_check_file(int fd_inp, int fd_out, char *str1, char *str2);
int		is_path(char *cmd);
void	detect_path_one(char *path, t_fd fd, char **cmd, char **envp);
void	detect_path_two(char *path, t_fd fd, char **cmd, char **envp);
void	exit_arguments(void);
int		end_process(int child1, int child2, t_fd fd);
#endif
