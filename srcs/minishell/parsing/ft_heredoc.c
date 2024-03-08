/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:38:04 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/08 19:00:34 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*heredoc_expand(char *line, t_env *env, t_data data, int *i)
{
	char	*str;
	char	*buffer;

	str = NULL;
	if (line[*i + 1] == '?')
	{
		str = ft_strjoin_free_free(&str, ft_itoa(data.env_var));
		(*i)++;
	}
	else if (!ft_isalnum(line[*i + 1]))
		str = ft_strjoinchar_free(&str, line[*i]);
	else
	{
		buffer = ft_strdup("");
		while (ft_isalpha(line[++(*i)]) || line[*i] == '_' || line[*i] == '?')
			buffer = ft_strjoinchar_free(&buffer, line[*i]);
		if (find_key(env, buffer))
			str = ft_strjoin_free_free(&str, ft_strdup(find_key(env, \
						buffer)->value));
		ft_free(1, &buffer);
	}
	return (str);
}

static char	*heredoc_parsing(char *line, t_env *env, t_data data)
{
	char	*str;
	int		i;

	i = -1;
	str = ft_strdup("");
	while (line[++i])
	{
		if (line[i] == '$')
			str = ft_strjoin_free(&str, heredoc_expand(line, env, data, &i));
		if (line[i])
			str = ft_strjoinchar_free(&str, line[i]);
	}
	return (str);
}

static char	*check_heredoc_stop(char **stop, bool *flag)
{
	char	*new_stop;
	int		i;

	new_stop = NULL;
	*flag = false;
	if (ft_ischarin('\'', *stop) || ft_ischarin('\"', *stop))
		*flag = true;
	i = -1;
	while ((*stop)[++i])
		if ((*stop)[i] != '\'' && (*stop)[i] != '\"')
			new_stop = ft_strjoinchar_free(&new_stop, (*stop)[i]);
	ft_free(1, stop);
	return (ft_strjoin_free(&new_stop, "\n"));
}

char	*ft_heredoc(char **stop, t_env *env, t_data data)
{
	char	*line;
	char	*temp;
	bool	flag;

	temp = NULL;
	*stop = check_heredoc_stop(stop, &flag);
	if (!(*stop))
		return (NULL);
	line = get_next_line(0);
	while ((line))
	{
		if (!ft_strcmp(line, *stop))
			break ;
		if (!flag)
			temp = ft_strjoin_free_free(&temp, heredoc_parsing(line, env, \
					data));
		else
			temp = ft_strjoin_free(&temp, line);
		ft_free(1, &line);
		line = get_next_line(0);
	}
	return (ft_free(1, &line), temp);
}
