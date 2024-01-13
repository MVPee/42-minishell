/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:37:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/01/13 21:48:30 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(void)
{
    char *line;

    while ((line = get_next_line(0)))
    {
        if (ft_strcmp(line, "exit\n") == 0)
            break;
        ft_printf("%s", line);
    }
    return (0);
}