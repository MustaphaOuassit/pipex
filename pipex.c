/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:42:40 by mouassit          #+#    #+#             */
/*   Updated: 2021/09/30 10:59:15 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    int fd;
    int fd_o;
    char **cmd;
    int id;
    int pipe_nb[2];
    
    fd = 0;
    fd_o = 0;
    if(argc >= 4)
    {
        if ((fd = open(argv[1], O_RDONLY)) > 0)
        {
            pipe(pipe_nb);
            cmd = ft_split(argv[2],' ');
            id = fork();
            if(id == 0)
            {
                close(pipe_nb[0]);
                dup2(fd,STDIN_FILENO);
                dup2(pipe_nb[1],STDOUT_FILENO);
                execve("/bin/cat", cmd, envp);
            }
            else
            {
                fd_o = open(argv[4],O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY, 0777);
                cmd = ft_split(argv[3],' ');
                close(pipe_nb[1]);
                dup2(pipe_nb[0],STDIN_FILENO);
                dup2(fd_o,STDOUT_FILENO);
                execve("/usr/bin/wc", cmd, envp);
            }

        }
        else
            write(1,"Error File\n",11);
    }
    else
        write(1,"Error\n",6);
    return(0);
}