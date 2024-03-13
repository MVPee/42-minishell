/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:39:00 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/13 10:29:25 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_node	*new_node(char *name, t_token token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	node->token = token;
	node->next = NULL;
	return (node);
}

void	append_node(t_node **head, char **name, t_token token)
{
	t_node	*new;
	t_node	*current;

	if (!name || !(*name));
		return ;
	new = new_node(*name, token);
	if (*head == NULL)
		*head = new;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
	ft_free(1, name);
}

static void	get_quotes(char *line, int *i, char **buffer)
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
