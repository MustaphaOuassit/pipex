/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:42:40 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/12 16:48:13 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	detect_path_one(char *path,int fd_inp,char **cmd,char **envp)
{
	if (path)
	{
		close(g_pipe_nb[0]);
		dup2(fd_inp, STDIN_FILENO);
		dup2(g_pipe_nb[1], STDOUT_FILENO);
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

void	detect_path_two(char *path,int fd_out,char **cmd,char **envp)
{
	if (path)
	{
		close(g_pipe_nb[1]);
		dup2(g_pipe_nb[0], STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
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

void	end_process(int child1, int child2)
{
	int	status;

	close(g_pipe_nb[0]);
	close(g_pipe_nb[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	child[2];
	int	status;
	int	i;

	i = 0;
	if (argc == 5)
	{
		pipe(g_pipe_nb);
		child[0] = fork();
		if (child[0] == 0)
			first_child(argv[2], argv[1], envp);
		else
		{
			child[1] = fork();
			if (child[1] == 0)
				second_child(argv[3], argv[4], envp);
			else
				end_process(child[0], child[1]);
		}
	}
	else
		exit_arguments();
	return (WEXITSTATUS(status));
}
