/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:42:40 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/10 12:53:36 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int child[2];
	int status;
	int i;
	
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
			if(child[1] == 0)
				second_child(argv[3], argv[4], envp);
			else
			{
				close(g_pipe_nb[0]);
				close(g_pipe_nb[1]);
				waitpid(child[0],&status,0);
				waitpid(child[1],&status,0);	
			}
		}
	}
	else
	{
		write(1, "Error arguments\n", 17);
		exit(EXIT_FAILURE);	
	}
	return (WEXITSTATUS(status));
}


