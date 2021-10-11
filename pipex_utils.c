/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 08:44:18 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/11 13:25:41 by mouassit         ###   ########.fr       */
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
	if ((cmd[0] == '/') && (access(cmd, F_OK)) == 0)
	{
		return (cmd);	
	}
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

void	first_child(char *argv, char *name_file, char **envp)
{
	char	**cmd;
	char	*path;
	int		fd_inp;

	fd_inp = open(name_file, O_RDONLY);
	if(fd_inp > 0)
	{
		cmd = ft_split(argv, ' ');
		if(!cmd[0])
			path = NULL;
		else
		{
			if(argv[0] == '/')
				path = argv;
			else
				path = get_path(envp, cmd[0]);	
		}
		if (path)
		{
			close(g_pipe_nb[0]);
			dup2(fd_inp, STDIN_FILENO);
			dup2(g_pipe_nb[1], STDOUT_FILENO);
			if(execve(path, cmd, envp) == -1)
			{
				perror(cmd[0]);	
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if(cmd[0])
				write(1, cmd[0], ft_strlen(cmd[0]));
			write(1,": command not found\n",20);
			exit(0);
		}	
	}
	else
	{
		perror(name_file);
		exit(EXIT_FAILURE);
	}
}

void	second_child(char *argv, char *name_file, char **envp)
{
	char	**cmd;
	char	*path;
	int		fd_out;

	fd_out = open(name_file, O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY, 0777);
	if(fd_out > 0)
	{
		cmd = ft_split(argv, ' ');
		if(!cmd[0])
			path = NULL;
		else
		{
			if(argv[0] == '/')
				path = argv;
			else
				path = get_path(envp, cmd[0]);	
		}
		if (path)
		{
			close(g_pipe_nb[1]);
			dup2(g_pipe_nb[0], STDIN_FILENO);
			dup2(fd_out, STDOUT_FILENO);
			if(execve(path, cmd, envp) == -1)
			{
				perror(cmd[0]);	
				exit(127);
			}
		}
		else
		{
			if(cmd[0])
				write(1, cmd[0], ft_strlen(cmd[0]));
			write(1,": command not found\n",20);
			exit(127);
		}		
	}
	else
	{
		perror(name_file);
		exit(EXIT_FAILURE);
	}
}
