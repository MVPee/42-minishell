/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:39:00 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/05 10:52:50 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char **get_cmd_splitted(char *line, int *count)
{
	char **split = NULL;
	char buffer[1000];

	int i = -1;
	int j = 0;
	while(line[++i])
	{
		if (line[i] == '\"')
		{
			buffer[j++] = line[i];
			while(line[++i] != '\"' && line[i])
			{
				buffer[j] = line[i];
				j++;
			}
			buffer[j++] = line[i];
		}
		else if (line[i] == '\'')
		{
			buffer[j++] = line[i];
			while(line[++i] != '\'' && line[i])
			{
				buffer[j] = line[i];
				j++;
			}
			buffer[j++] = line[i];
		}
		else if (line[i] == '|')
		{
			buffer[j] = '\0';
			split = ft_splitjoin(split, buffer);
			if (!split)
				return (NULL);
			(*count)++;
			ft_memset(buffer, 0, 1000);
			j = 0;
		}
		else
		{
			buffer[j] = line[i];
			j++;
		}
		if (!line[i])
			break;
	}
	buffer[j] = '\0';
	(*count)++;
	split = ft_splitjoin(split, buffer);
	if (!split)
		return (NULL);
	ft_memset(buffer, 0, 1000);
	return split;
}

int	number_of_cmd(char *line)
{
	int	i;
	int	flag;
	int	count;

	flag = 0;
	count = 1;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
			while (line[i != '\''] && line[i])
				i++;
		else if (line[i] == '\"')
			while (line[i != '\"'] && line[i])
				i++;
		else if (line[i] == '|')
			count++;
		if (!line[i])
			break ;
	}
	return (count);
}

void free_lexer(t_lexer *lexer)
{
    if (lexer) {
        if (lexer->cmd) {
            free(lexer->cmd);
            lexer->cmd = NULL;
        }
        
        t_node *current = lexer->head;
        while (current) {
            t_node *temp = current;
            current = current->next;
            free(temp->name);
            free(temp);
        }
        
        lexer->head = NULL;
        
        free(lexer);
    }
}