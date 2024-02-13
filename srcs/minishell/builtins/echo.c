/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:46:20 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/02/13 11:20:33 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void ft_echo(t_env env, char **split)
{
    int i;
    bool flag;

    flag = true;
    i = 0;
    while(split[++i])
    {
        if (i == 1 && ft_strncmp(split[i], "-n\0", 3) == 0)
        {
            i++;
            flag = false;
        }
        if (split[i + 1] == NULL)
            ft_printf("%s", split[i]);
        else
            ft_printf("%s ", split[i]);
    }
    if (flag)
        ft_printf("\n");
}
