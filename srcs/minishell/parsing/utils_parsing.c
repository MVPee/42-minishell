/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:38:04 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/26 17:33:45 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *ft_heredoc(char *stop)
{
    char *line = NULL;
    char *temp = NULL;

    ft_printf("> ");
    while ((line = get_next_line(0)))
    {
        if (!ft_strcmp(line, ft_strjoin(stop, "\n")))
        {
            if (!temp)
                temp = ft_strdup("");
            break;
        }
        if (!temp)
            temp = ft_strdup(line);
        else
        {
            char *tmp = ft_strjoin(temp, line);
            free(temp);
            temp = tmp;
        }
        ft_printf("> ");
        free(line);
    }
    free(line);
    return (temp);
}
