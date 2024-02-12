/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:37:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/12 17:17:08 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(void)
{
    char *line;

    while ((line = get_next_line(0)))
    {
        if (ft_strcmp(line, "exit\n") == 0)
        {
            free(line);
            break;
        }
        ft_printf("%s", line);
        free(line);
    }
    return (0);
}