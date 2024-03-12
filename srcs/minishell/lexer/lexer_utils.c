/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:39:00 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/12 15:11:09 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void get_quotes(char *line, int *i, char **buffer)
{
	if (line[*i] == '\"')
	{
		*buffer = ft_strjoinchar_free(buffer, line[*i]);
		while (line[++(*i)] != '\"' && line[*i])
			*buffer = ft_strjoinchar_free(buffer, line[*i]);
	}
	else if (line[*i] == '\'')
	{
		*buffer = ft_strjoinchar_free(buffer, line[*i]);
		while (line[++(*i)] != '\'' && line[*i])
			*buffer = ft_strjoinchar_free(buffer, line[*i]);
	}
}

char	**get_cmd_splitted(char *line, int *count)
{
	char	**split;
	char	*buffer;
	int		i;

	split = NULL;
	buffer = NULL;
	i = -1;
	while (line[++i])
	{
		get_quotes(line, &i, &buffer);
		if (line[i] == '|')
		{
			split = ft_splitjoin(split, buffer);
			if (split)
				(*count)++;
			ft_free(1, &buffer);
		}
		else
			buffer = ft_strjoinchar_free(&buffer, line[i]);
	}
	split = ft_splitjoin(split, buffer);
	if (split)
		(*count)++;
	return (ft_free(1, &buffer), split);
}

void	free_lexer(t_lexer *lexer)
{
	t_node	*current;
	t_node	*temp;

	if (lexer)
	{
		if (lexer->cmd)
		{
			free(lexer->cmd);
			lexer->cmd = NULL;
		}
		current = lexer->head;
		while (current)
		{
			temp = current;
			current = current->next;
			free(temp->name);
			free(temp);
		}
		lexer->head = NULL;
		ft_free(1, &lexer);
	}
}
