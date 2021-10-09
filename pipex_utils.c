/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 08:44:18 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/09 11:52:01 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_two(char **table)
{
	int	i;

	i = 0;
	while (table[i] != '\0')
	{
		free(table[i]);
		i++;
	}
	free(table);
}

char	*path_line(char **line, char *cmd)
{
	char	*cmdjoin;
	char	*cmdlist;
	int		j;
	char	**tmp;

	j = 0;
	tmp = line;
	line = ft_split(line[1], ':');
	free_two(tmp);
	while (line[j] != '\0')
	{
		cmdlist = ft_strjoin("/", cmd);
		cmdjoin = ft_strjoin(line[j], cmdlist);
		if (access(cmdjoin, F_OK) == 0)
		{
			free_two(line);
			free(cmdlist);
			return (cmdjoin);
		}
		j++;
		free(cmdjoin);
		free(cmdlist);
	}
	free_two(line);
	return (NULL);
}

char	*get_path(char **envp, char *cmd)
{
	int		i;
	char	**line;
	char	*path;

	i = 0;
	path = NULL;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (envp[i] != '\0')
	{
		line = ft_split(envp[i], '=');
		if (!ft_strncmp(line[0], "PATH"))
		{
			path = path_line(line, cmd);
			if (path)
				return (path);
			break ;
		}
		free_two(line);
		i++;
	}
	return (path);
}

void	parent_process(char *argv, int file, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = get_path(envp, cmd[0]);
	if (path)
	{
		close(g_pipe_nb[0]);
		dup2(file, STDIN_FILENO);
		dup2(g_pipe_nb[1], STDOUT_FILENO);
		execve(path, cmd, envp);
	}
	else
	{
		write(1, cmd[0], ft_strlen(cmd[0]));
		write(1,": command not found\n",20);
		exit(EXIT_FAILURE);
	}
}

void	child_process(char *argv, int file, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = get_path(envp, cmd[0]);
	if (path)
	{
		close(g_pipe_nb[1]);
		dup2(g_pipe_nb[0], STDIN_FILENO);
		dup2(file, STDOUT_FILENO);
		execve(path, cmd, envp);
	}
	else
	{
		write(1, cmd[0], ft_strlen(cmd[0]));
		write(1,": command not found\n",20);
		exit(EXIT_FAILURE);
	}
}
