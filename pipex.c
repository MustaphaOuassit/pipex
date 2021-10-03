/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:42:40 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/03 10:23:15 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd_inp;
	int	fd_out;
	int	id;

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
			else
				child_process(argv[3], fd_out, envp);
		}
		else
			write(1, "Error File\n", 11);
	}
	else
		write(1, "Error\n", 6);
	return (0);
}
