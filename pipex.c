/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:42:40 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/09 12:56:37 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd_inp;
	int	fd_out;
	int	id;
	int child;
	int status;

	fd_inp = 0;
	fd_out = 0;
	if (argc == 5)
	{
		fd_inp = open(argv[1], O_RDONLY);
		fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY, 0777);
		if ((fd_inp > 0) && (fd_out > 0))
		{
			pipe(g_pipe_nb);
			id = fork();
			if (id == 0)
			parent_process(argv[2], fd_inp, envp);
			child = fork();
			if(child == 0)
				child_process(argv[3], fd_out, envp);
			wait(&status);
			if(WIFEXITED(status))
				exit(WEXITSTATUS(status));
		}
		else
		{
			perror(ft_check_file(fd_inp,fd_out,argv[1],argv[2]));
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		write(1, "Error arguments\n", 17);
		exit(EXIT_FAILURE);	
	}
	return (0);
}
