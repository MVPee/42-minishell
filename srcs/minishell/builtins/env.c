/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:37:37 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/14 21:32:05 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_env(t_data *data, t_env *head, char **split)
{
	if (split[1])
    {
        ft_printf("env: %s: No such file or directory\n", split[1]);
        data->env_var = 127;
    }
		
	else
    {
        get_env(head);
        ft_printf("_=/usr/bin/env\n");
        data->env_var = 0;
    }
		
}
