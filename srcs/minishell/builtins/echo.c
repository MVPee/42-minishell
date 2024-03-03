/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:46:20 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/03/03 14:46:04 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void ft_echo(t_data *data, char **split)
{
    bool flag;
    int i;

    flag = true;
    i = 0;
    if (!split[1])
    {
        ft_printf("\n");
        return ;
    }
    if (!ft_strcmp(split[1], "-n"))
    {
        i++;
        flag = false;
    }
    while(split[++i])
    {
        ft_printf("%s", split[i]);
        if (split[i + 1])
            ft_printf(" ");
    }
    if (flag)
        ft_printf("\n");
    data->env_var = 0;
}
