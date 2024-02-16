/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:18:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/16 18:30:45 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void check_cmd(char *str)
{
    char **split = ft_split(str, " ");
    while(*split)
    {
        ft_printf("%s\n", *split++);
    }
}

void parsing(char *line)
{
    t_cmd *cmd;
    char **split;
    int i;
    
    cmd = NULL;
    ft_printf("line: %s\n", line);
    split = ft_split(line, "|");
    i = -1;
    while(split[++i])
    {
        check_cmd(split[i]);
    }
}