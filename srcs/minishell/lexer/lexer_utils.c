/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:39:00 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/03 15:09:06 by mvpee            ###   ########.fr       */
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
			while(line[++i] != '\"')
			{
				buffer[j] = line[i];
				j++;
			}
			buffer[j++] = line[i];
		}
		else if (line[i] == '\'')
		{
			buffer[j++] = line[i];
			while(line[++i] != '\'')
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

static bool	check_after(char *line, int i)
{
	int	j;

	j = i;
	while (line[++j])
	{
		while(line[j] == ' ')
			j++;
		if (ft_isprint(line[j]))
			return false;
		else if (line[j] == '|')
			return (true);
		else if (!line[j])
			return (true);
	}
	return (true);
}

static bool	check_before(char *line, int i)
{
	int	j;

	j = i;
	if (j == 0)
		return (true);
	while (line[--j])
	{
		while(line[j] == ' ')
			j--;
		if (ft_isprint(line[j]))
			return false;
		else if (line[j] == '|')
			return (true);
		else if (!line[j])
			return (true);
		if (j == 0)
			return (true);
	}
	return (false);
}

bool	check_after_pipe_and_semicolon(char *str)
{
	int	i;
	char *line = ft_strtrim(str, " ");

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] != '\"' && line[i])
				i++;
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'' && line[i])
				i++;
		}
		else if (line[i] == ';')
		{
			if (line[i + 1])
				return (ft_printf("syntax error near unexpected token '%c'\n", line[i + 1]), true);
			return (ft_printf("syntax error near unexpected token 'newline'\n"), true);
		}
		else if (line[i] == '|')
		{
			if (check_before(line, i))
				return (ft_printf("syntax error near unexpected token '|'\n"), true);
			if (check_after(line, i))
				return (ft_printf("syntax error near unexpected token '|'\n"), true);
		}
		else if (line[i] == '<')
		{
			if (line[i + 1] == '>')
				return (ft_printf("syntax error near unexpected token <'\n"), true);
			if (line[i + 1] == '<')
			{
				i = i + 2;
				while(line[i] == ' ')
					i++;
				if (ft_ischarin(line[i], "<>|") || !line[i])
					return (ft_printf("syntax error near unexpected token '<'\n"), true);
			}
			else
			{
				i++;
				while(line[i] == ' ')
					i++;
				if (ft_ischarin(line[i], "<>|") || !line[i])
					return (ft_printf("syntax error near unexpected token '<'\n"), true);
			}
			i--;
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '<')
				return (ft_printf("syntax error near unexpected token '>'\n"), true);
			if (line[i + 1] == '>')
			{
				i = i + 2;
				while(line[i] == ' ')
					i++;
				if (ft_ischarin(line[i], "<>|") || !line[i])
					return (ft_printf("syntax error near unexpected token '>'\n"), true);
			}
			else
			{
				i++;
				while(line[i] == ' ')
					i++;
				if (ft_ischarin(line[i], "<>|") || !line[i])
					return (ft_printf("syntax error near unexpected token '>'\n"), true);
			}
			i--;
		}
		if (!line[i])
			break ;
	}
	return (false);
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