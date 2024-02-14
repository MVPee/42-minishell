/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:37:37 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/14 15:49:53 by mvan-pee         ###   ########.fr       */
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
