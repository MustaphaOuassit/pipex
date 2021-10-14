/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:42:40 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/14 11:02:21 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		*child;
	t_fd	fd;
	int		status;

	child = (int *)malloc(sizeof(int) * 2);
	fd.pipe = (int *)malloc(sizeof(int) * 2);
	if (argc == 5)
	{
		pipe(fd.pipe);
		child[0] = fork();
		if (child[0] == 0)
			first_child(argv[2], argv[1], envp, fd);
		else
		{
			child[1] = fork();
			if (child[1] == 0)
				second_child(argv[3], argv[4], envp, fd);
			else
				status = end_process(child[0], child[1], fd);
		}
	}
	else
		exit_arguments();
	return (WEXITSTATUS(status));
}
