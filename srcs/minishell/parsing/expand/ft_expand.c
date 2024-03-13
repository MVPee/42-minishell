/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:12:13 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/13 16:09:23 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static char	*ft_expand_double_quotes(char *line, t_env *head, t_data data, \
		int *i)
{
	char	*buffer;

	buffer = NULL;
	while (line[++(*i)] != '\"' && line[*i])
	{
		if (line[*i] == '$' && (ft_isalpha(line[*i + 1]) || \
			line[*i + 1] == '?'))
			buffer = ft_strjoin_free_free(&buffer, ft_expand_env(line, head, \
					data, i));
		else
			buffer = ft_strjoinchar_free(&buffer, line[*i]);
	}
	return (buffer);
}

char	*ft_expand2(char *line, t_env *head, t_data data, int *i)
{
	char	*buffer;

	buffer = NULL;
	if (line[*i] == '\"')
		buffer = ft_strjoin_free_free(&buffer, ft_expand_double_quotes(line, \
				head, data, i));
	if (line[*i] == '\'')
		while (line[++(*i)] != '\'')
			buffer = ft_strjoinchar_free(&buffer, line[*i]);
	if (line[*i] == '\\')
		if (line[++(*i)] == '\\')
			buffer = ft_strjoinchar_free(&buffer, line[(*i)++]);
	if (line[*i] == '$')
		buffer = ft_strjoin_free_free(&buffer, ft_expand_env(line, head, data, \
				i));
	else if (ft_isprint(line[*i]) && line[*i] != '\'' && line[*i] != '\"' \
		&& line[*i] != ' ')
		buffer = ft_strjoinchar_free(&buffer, line[*i]);
	return (buffer);
}

char	**ft_expand(char *line, t_env *head, t_data data)
{
	char	**split;
	char	*buffer;
	int		i;

	split = NULL;
	i = -1;
	while (line[++i])
	{
		ft_expand_home(line, &i, &buffer);
		if (line[i] != ' ')
			buffer = ft_strjoin_free_free(&buffer, ft_expand2(line, head, data, \
					&i));
		if (line[i] == ' ' && line[i])
		{
			if (buffer)
				split = ft_splitjoin(split, buffer);
			ft_free(1, &buffer);
		}
		if (!line[i])
			break ;
	}
	if (buffer)
		split = ft_splitjoin(split, buffer);
	return (ft_free(1, &buffer), split);
}
