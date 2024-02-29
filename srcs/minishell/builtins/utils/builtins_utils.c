/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:34:21 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/28 16:37:30 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void result_check(char **result, char *string, bool *stop_join)
{
    *result = ft_strdup(string);
    if (!*result)
    {
        free(string);
        *stop_join = true;
        return ;
    }
}

static void update_result(char **result, char *string, bool *stop_join)
{
    char    *temp;
    
    temp = ft_strjoin(*result, string);
    free(*result);
    if (!temp)
    {
        free(string);
        *stop_join = true;
        return ;
    }
    *result = temp;
}

char    *ft_multi_strjoin(int number_of_strings, ...)
{
    va_list args;
    bool    stop_join;
    char    *result;
    char    *string;
    size_t  i;
    
    va_start(args, number_of_strings);
    i = 0;
    result = NULL;
    stop_join = false;
    while (i++ < number_of_strings && !stop_join)
    {
        string = va_arg(args, char *);
        if (!string)
            if (result)
               return (free(result), va_end(args), NULL); 
        if (!result)
            result_check(&result, string, &stop_join);
        else
            update_result(&result, string, &stop_join);
    }
    va_end(args);
    return (result);
}
