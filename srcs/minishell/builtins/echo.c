/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:46:20 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/02/29 12:50:12 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_echo(t_data *data, char **split)
{
    char *result= ft_strdup("");
    char *temp;
    int i = 0;
    if (!split[i + 1])
        return (free(result), ft_strdup("\n"));
    while(split[++i])
    {
        temp = ft_strjoin_free(result, split[i]);
        result = temp;
        if (split[i + 1])
        {
            temp = ft_strjoin_free(result, " ");
            result = temp;
        }
    }
    temp = ft_strjoin_free(result, "\n");
    result = temp;
    return (result);
}
