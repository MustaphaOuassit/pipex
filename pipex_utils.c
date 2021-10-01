/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 08:44:18 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/01 11:57:41 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *get_path(char **envp, char *cmd)
{
    int i;
    int j;
    char **line;
    char *path;

    i = 0;
    j = 0;
    path = NULL;
    if(access(cmd,F_OK) == 0)
        path = cmd;
    else
    {
        while (envp[i] != '\0')
        {
            line = ft_split(envp[i],'=');
            if(!ft_strncmp(line[0],"PATH"))
            {
                line = ft_split(line[1],':');
                while (line[j] != '\0')
                {
                    if(access(ft_strjoin(line[j],ft_strjoin("/",cmd)),F_OK) == 0)
                    {
                        path = ft_strjoin(line[j],ft_strjoin("/",cmd));
                        break;   
                    }
                    j++;
                }
                break;
            }
            i++;
        }   
    }
    return(path);
}