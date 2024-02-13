/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:37:37 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/13 13:58:00 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void ft_env(t_env env, char **split)
{
    int i;

    i = -1;
    if (split[1])
    {
        ft_printf("env : %s: No such file or directory\n", split[1]);
        env.var_env = 127;
        return ;
    }
    else
        while(env.env[++i])
            ft_printf("%s\n", env.env[i]);
    env.var_env = 0;
}