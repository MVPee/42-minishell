/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_home.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:27:04 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/11 10:38:59 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	ft_expand_home2(char *line, int *i, char **buffer)
{
	char	*value;
	int		p;

	value = getenv("HOME");
	if (value)
	{
		p = -1;
		while (value[++p])
			*buffer = ft_strjoinchar_free(buffer, value[p]);
	}
	(*i)++;
}

void	ft_expand_home(char *line, int *i, char **buffer)
{
	char	*value;
	int		p;

	value = NULL;
	if (*i == 0)
	{
		*buffer = NULL;
		if (line[*i] == '~' && (line[*i + 1] == ' ' || !line[*i + 1]))
		{
			value = getenv("HOME");
			if (value)
			{
				p = -1;
				while (value[++p])
					*buffer = ft_strjoinchar_free(buffer, value[p]);
			}
			(*i)++;
		}
	}
	else if (line[*i] == '~' && line[*i - 1] == ' ' && (line[*i + 1] == ' ' \
			|| !line[*i + 1]))
		ft_expand_home2(line, i, buffer);
}
