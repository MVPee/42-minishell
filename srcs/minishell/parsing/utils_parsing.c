/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:38:04 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/05 12:46:08 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// static char	*ft_split_to_str(char **split, bool free)
// {
// 	char	*str;
// 	int		i;

// 	if (!split)
// 		return (NULL);
// 	str = NULL;
// 	i = -1;
// 	while (split[++i])
// 	{
// 		if (!str)
// 			str = ft_strdup("");
// 		str = ft_strjoin_free(str, split[i]);
// 		if (split[i + 1])
// 			str = ft_strjoin_free(str, " ");
// 	}
// 	if (free)
// 		ft_free_matrix(1, &split);
//     str = ft_strjoin_free(str, "\n");
// 	return (str);
// }

static char	*ft_strjoinchar_free(char *s1, char s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		str[j++] = s1[i];
	i = -1;
	str[j++] = s2;
	str[j] = '\0';
	ft_free(1, &s1);
	return (str);
}

static char *heredoc_parsing(char *line, t_env *env, t_data data)
{
    char *str;
    char *buffer;
    int i;

    i = -1;
    str = ft_strdup("");
    while(line[++i])
    {
        if (line[i] == '$')
        {
            buffer = ft_strdup("");
            while(ft_isalpha(line[++i]) || line[i] == '_' || line[i] == '?')
                buffer = ft_strjoinchar_free(buffer, line[i]);
            if (!ft_strcmp(buffer, "?"))
            {
                str = ft_strjoin_free(str, ft_itoa(data.env_var));
                str = ft_strjoin_free(str, "\n");
            }
            else
            {
                if (find_key(env, buffer))
                {
                    char *value = ft_strdup(find_key(env, buffer)->value);
                    str = ft_strjoin_free(str, value);
                    free(value);
                    str = ft_strjoin_free(str, "\n");
                }
            }
        }
        else
            str = ft_strjoinchar_free(str, line[i]);
    }
    return (str);
}

static char *check_heredoc_stop(char *stop, bool *flag)
{
    char *new_stop;
    int i;

    new_stop = ft_strdup("");
    *flag = false;
    if (ft_ischarin('\'', stop) || ft_ischarin('\"', stop))
        *flag = true;
    i = -1;
    while(stop[++i])
        if (stop[i] != '\'' && stop[i] != '\"')
            new_stop = ft_strjoinchar_free(new_stop, stop[i]);
    free(stop);
    return new_stop;
}

char *ft_heredoc(char *stop, t_env *env, t_data data)
{
    char *line = NULL;
    char *temp = NULL;
    bool flag;

    stop = check_heredoc_stop(stop, &flag);
    ft_printf("> ");
    while ((line = get_next_line(0)))
    {
        if (!ft_strcmp(line, ft_strjoin(stop, "\n")))
        {
            if (!temp)
                temp = ft_strdup("");
            break;
        }
        if (!temp)
            temp = ft_strdup("");
        if (!flag)
            temp = ft_strjoin_free(temp, heredoc_parsing(line, env, data));
        else
            temp = ft_strjoin_free(temp, line);
        ft_printf("> ");
        free(line);
    }
    free(line);
    return (temp);
}
