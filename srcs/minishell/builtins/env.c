/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:37:37 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/27 20:59:23 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_env(t_data *data, t_env *head, char **split)
{
    char *result;
    char *temp;

    if (split[1])
    {
        result = ft_strjoin("env: '", split[1]);
        temp = ft_strjoin(result, "' No such file or directory\n");
        free(result);
        result = temp;
        data->env_var = 127;
    }
	else
    {
        while (head)
        {
            temp = ft_strjoin(result, head->key);
            result = temp;

            temp = ft_strjoin(result, "=");
            free(result);
            result = temp;

            temp = ft_strjoin(result, head->value);
            free(result);
            result = temp;

            temp = ft_strjoin(result, "\n");
            free(result);
            result = temp;

            head = head->next;
        }
        temp = ft_strjoin(result, "_=/usr/bin/env\n");
        free(result);
        result = temp;
        data->env_var = 0;
    }
    return (result);
}

