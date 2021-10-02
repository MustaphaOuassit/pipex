/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouassit <mouassit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 08:44:18 by mouassit          #+#    #+#             */
/*   Updated: 2021/10/02 11:21:50 by mouassit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    free_two(char **table)
{
    int i;

    i = 0;
    while (table[i] != '\0')
    {
        free(table[i]);
        i++;
    }
    free(table);
}

char    *get_path(char **envp, char *cmd)
{
    int i;
    int j;
    char **line;
    char *path;
    char *cmdjoin;
    char *cmdlist;
    char **tmp;

    i = 0;
    j = 0;
    path = NULL;
    if(access(cmd,F_OK) == 0)
        return(cmd);
    else
    {
        while (envp[i] != '\0')
        {
            line = ft_split(envp[i],'=');
            if(!ft_strncmp(line[0],"PATH"))
            {
                tmp = line;
                line = ft_split(line[1],':');
                free_two(tmp);
                while (line[j] != '\0')
                {
                    cmdlist = ft_strjoin("/",cmd);
                    cmdjoin = ft_strjoin(line[j], cmdlist);
                    if(access(cmdjoin,F_OK) == 0)
                    {
                        free_two(line);
                        free(cmdjoin);
                        free(cmdlist);
                        return(cmdjoin);
                    }
                    j++;
                    free(cmdjoin);
                    free(cmdlist);
                }
                free_two(line);
                break;
            }
            free_two(line);
            i++;
        }
    }
    return(path);
}