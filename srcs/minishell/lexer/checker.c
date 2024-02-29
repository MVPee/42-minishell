/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:46:23 by mvan-pee          #+#    #+#             */
/*   Updated: 2024/02/29 22:35:32 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool check_after_pipe_and_semicolon(char *line)
{
	char **split;
	int i;

	split = ft_split(line, " ");
	i = -1;
	while(split[++i])
	{
		if (!ft_strcmp(split[i], ";"))
		{
			if (split[i + 1])
				return(ft_printf("syntax error near unexpected token '%s'\n", split[i + 1]), ft_free(1, &split), true);
			return (ft_free(1, &split), ft_printf("syntax error near unexpected token 'newline'\n"), true);
		}
		if (!ft_strcmp(split[i], "|") && !split[i + 1])
			return (ft_free(1, &split), ft_printf("syntax error near unexpected token 'newline'\n"), true);
	}
	return (false);
}

static char *check_variable(char *line, t_env *head, t_data data)
{
    int i = -1;
    int j;
    int k;
    int p;
    char buffer[10000];
    char buffer2[500];
    char *value;
    int flag = 0;

    j = 0;
    k = 0;
    while(line[++i])
    {
        if(i >= 1)
        {
            if (line[i] == '~' && line[i - 1] == ' ' && (line[i + 1] == ' ' || !line[i + 1]))
            {
                if (find_key(head, "HOME"))
                {
                    if (value = find_key(head, "HOME")->value)
                    {
                        p = -1;
                        while(value[++p])
                        {
                            buffer[j] = value[p];
                            j++;
                        }
                    }
                }
                else
                    buffer[j++] = '~';
                i++;
            }
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
        }
        else if (line[i] == '\'')
        {
            while(line[++i] != '\'' && line[i])
            {
                buffer[j] = line[i];
                j++;
            }
        }
        else if (line[i] == '$')
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
                i--;
                buffer2[k] = '\0';
                if (find_key(head, buffer2))
                {
                    value = ft_strdup(find_key(head, buffer2)->value);
                    ft_memset(buffer2, 0, 500);
                    k = 0;
                    p = -1;
                    while(value[++p])
                    {
                        buffer[j] = value[p];
                        j++;
                    }
                }
            }
        }
        else
            buffer[j++] = line[i];
        if (!line[i])
            break;
    }
    buffer[j] = '\0';
    return (ft_strdup(buffer));
}

char *checker(char *line, t_env *head, t_data data)
{
    char *new_line = NULL;

	if (check_after_pipe_and_semicolon(line))
		return (NULL);
    new_line = check_variable(line, head, data);
	return (new_line);
}
