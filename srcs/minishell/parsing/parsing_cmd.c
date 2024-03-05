/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:12:13 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/05 11:39:48 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char **parsing_cmd(char *line, t_env *head, t_data data)
{
    char **split = NULL;
    int i = -1;
    char buffer[10000];
    int j = 0;
    char buffer2[1000];
    int k = 0;
    char *value;
    int p = 0;

    while(line[++i])
    {
        if (i == 0)
        {
            if (line[i] == '~' && (line[i + 1] == ' ' || !line[i + 1]))
            {
                if (value = getenv("HOME"))
                {
                    p = -1;
                    while(value[++p])
                    {
                        buffer[j] = value[p];
                        j++;
                    }
                }
                i++;
            }
        }
        else if (line[i] == '~' && line[i - 1] == ' ' && (line[i + 1] == ' ' || !line[i + 1]))
        {
            if (value = getenv("HOME"))
            {
                p = -1;
                while(value[++p])
                {
                    buffer[j] = value[p];
                    j++;
                }
            }
            i++;
        }
        if (line[i] == '\"')
        {
            while(line[++i] != '\"' && line[i])
            {
                if (line[i] == '$')
                {
                    if (line[i + 1] == '?')
                    {
                        i++;
                        value = ft_itoa(data.env_var);
                        p = -1;
                        while(value[++p])
                        {
                            buffer[j] = value[p];
                            j++;
                        }
                    }
                    else
                    {
                        while(ft_isalnum(line[++i]))
                        {
                            buffer2[k] = line[i];
                            k++;
                        }
                        buffer2[k] = '\0';
                        if (find_key(head, buffer2))
                        {
                            value = ft_strdup(find_key(head, buffer2)->value);
                            p = -1;
                            while(value[++p])
                            {
                                buffer[j] = value[p];
                                j++;
                            }
                        }
                        ft_memset(buffer2, 0, 500);
                        k = 0;
                        i--;
                    }
                }
                else
                {
                    buffer[j++] = line[i];
                }
            }
            i++;
        }
        if (line[i] == '\'')
        {
            while(line[++i] != '\'' && line[i])
            {
                buffer[j] = line[i];
                j++;
            }
        }
        if (line[i] == '\\')
            if (line[++i] == '\\')
                buffer[j++] = line[i++];
        if (line[i] == '$')
        {
            if (line[i + 1] == '?')
            {
                i++;
                value = ft_itoa(data.env_var);
                p = -1;
                while(value[++p])
                {
                    buffer[j] = value[p];
                    j++;
                }
            }
            else
            {
                while(ft_isalnum(line[++i]))
                {
                    buffer2[k] = line[i];
                    k++;
                }
                buffer2[k] = '\0';
                if (find_key(head, buffer2))
                {
                    value = ft_strdup(find_key(head, buffer2)->value);
                    p = -1;
                    while(value[++p])
                    {
                        buffer[j] = value[p];
                        j++;
                    }
                }
                ft_memset(buffer2, 0, 500);
                k = 0;
                i--;
            }
            i++;
        }
        if (line[i] == ' ')
        {
            buffer[j] = '\0';
            if (buffer[0] != '\0')
                split = ft_splitjoin(split, buffer);
            ft_memset(buffer, 0, 10000);
            j = 0;
        }
        if (ft_isprint(line[i]) && line[i] != '\'' && line[i] != '\"' && line[i] != ' ')
            buffer[j++] = line[i];
            
        if (!line[i])
            break;
    }
    buffer[j] = '\0';
    if (buffer[0] != '\0')
        split = ft_splitjoin(split, buffer);
    ft_memset(buffer, 0, 10000);
    return (split);
}
