/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:38:04 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/08 09:44:31 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*heredoc_parsing(char *line, t_env *env, t_data data)
{
	char	*str;
	char	*buffer;
	int		i;
	char	*value;

	i = -1;
	str = ft_strdup("");
	while (line[++i])
	{
		if (line[i] == '$')
		{
			if (line[i + 1] == '?')
			{
				str = ft_strjoin_free(str, ft_itoa(data.env_var));
				i++;
			}
			else if (!ft_isalnum(line[i + 1]))
                str = ft_strjoinchar_free(str, line[i]);
			else
			{
				buffer = ft_strdup("");
				while (ft_isalpha(line[++i]) || line[i] == '_' \
					|| line[i] == '?')
					buffer = ft_strjoinchar_free(buffer, line[i]);
				if (find_key(env, buffer))
				{
					value = ft_strdup(find_key(env, buffer)->value);
					str = ft_strjoin_free(str, value);
					free(value);
					str = ft_strjoin_free(str, "\n");
				}
				free(buffer);
			}
		}
		else
			str = ft_strjoinchar_free(str, line[i]);
	}
	return (str);
}

static char	*check_heredoc_stop(char *stop, bool *flag)
{
	char	*new_stop;
	int		i;

	new_stop = ft_strdup("");
	*flag = false;
	if (ft_ischarin('\'', stop) || ft_ischarin('\"', stop))
		*flag = true;
	i = -1;
	while (stop[++i])
		if (stop[i] != '\'' && stop[i] != '\"')
			new_stop = ft_strjoinchar_free(new_stop, stop[i]);
	return (new_stop);
}

char	*ft_heredoc(char *stop, t_env *env, t_data data)
{
	char	*line;
	char	*temp;
	bool	flag;

	temp = NULL;
	stop = check_heredoc_stop(stop, &flag);
    ft_printf("> ");
	while ((line = get_next_line(0)))
	{
		if (!ft_strcmp(line, ft_strjoin(stop, "\n")))
		{
			if (!temp)
				temp = ft_strdup("");
			break ;
		}
        ft_printf("> ");
		if (!temp)
			temp = ft_strdup("");
		if (!flag)
			temp = ft_strjoin_free(temp, heredoc_parsing(line, env, data));
		else
			temp = ft_strjoin_free(temp, line);
		free(line);
	}
	free(line);
	return (temp);
}
