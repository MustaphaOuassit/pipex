/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:42:40 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/02 11:26:00 by mouassit         ###   ########.fr       */
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
    char *path;
    
    fd = 0;
    fd_o = 0;
    if(argc == 5)
    {
        fd = open(argv[1], O_RDONLY);
        fd_o = open(argv[4],O_WRONLY | O_CREAT | O_TRUNC | O_RDONLY, 0777);
        if ((fd > 0) && (fd_o > 0))
        {
            pipe(pipe_nb);
            id = fork();
            if(id == 0)
            {
                cmd = ft_split(argv[2],' ');
                path = get_path(envp,cmd[0]);
                if(path)
                {
                    close(pipe_nb[0]);
                    dup2(fd,STDIN_FILENO);
                    dup2(pipe_nb[1],STDOUT_FILENO);
                    execve(path, cmd, envp);
                }
                else
                    write(1,"Error cmd\n",11);
            }
            else
            {
                cmd = ft_split(argv[3],' ');
                path = get_path(envp,cmd[0]);
                if(path)
                {
                    close(pipe_nb[1]);
                    dup2(pipe_nb[0],STDIN_FILENO);
                    dup2(fd_o,STDOUT_FILENO);
                    execve(path, cmd, envp);  
                }
                else
                    write(1,"Error cmd\n",11);
            }
        }
        else
            write(1,"Error File\n",11);
    }
    else
        write(1,"Error\n",6);
    return(0);
}