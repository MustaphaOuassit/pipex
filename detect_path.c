/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:25:55 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/13 09:58:37 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	detect_path_one(char *path, t_fd fd, char **cmd, char **envp)
{
	if (path)
	{
		close(fd.pipe[0]);
		dup2(fd.inp, STDIN_FILENO);
		dup2(fd.pipe[1], STDOUT_FILENO);
		if (execve(path, cmd, envp) == -1)
		{
			perror(cmd[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (is_path(cmd[0]))
			perror(cmd[0]);
		else
		{
			if (cmd[0])
				write(1, cmd[0], ft_strlen(cmd[0]));
			write(1, ": command not found\n", 20);
		}
		exit(0);
	}
}

void	detect_path_two(char *path, t_fd fd, char **cmd, char **envp)
{
	if (path)
	{
		close(fd.pipe[1]);
		dup2(fd.pipe[0], STDIN_FILENO);
		dup2(fd.out, STDOUT_FILENO);
		if (execve(path, cmd, envp) == -1)
		{
			perror(cmd[0]);
			exit(127);
		}
	}
	else
	{
		if (is_path(cmd[0]))
			perror(cmd[0]);
		else
		{
			if (cmd[0])
				write(1, cmd[0], ft_strlen(cmd[0]));
			write(1, ": command not found\n", 20);
		}
		exit(127);
	}
}

void	exit_arguments(void)
{
	write(1, "Error arguments\n", 17);
	exit(EXIT_FAILURE);
}

int	end_process(int child1, int child2, t_fd fd)
{
	int	status;

	close(fd.pipe[0]);
	close(fd.pipe[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	return (status);
}
