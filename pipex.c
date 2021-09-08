/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:42:40 by mouassit          #+#    #+#             */
/*   Updated: 2021/09/08 11:51:59 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv)
{
    int fd;
    char *line;
    
    fd = 0;
    if(argc == 2)
    {
        if ((fd = open(argv[1], O_RDONLY)) > 0)
        {
            get_next_line(fd,&line);
            printf("%s\n",line);
        }
        else
            write(1,"Error File\n",11);
    }
    else
        write(1,"Error\n",6);
    return(0);
}