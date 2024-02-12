/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:37:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/12 17:53:24 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(void)
{
    char *line = NULL;

    while (777)
    {
        line = readline("minihell: ");
        if (ft_strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }
    }
    return (0);
}