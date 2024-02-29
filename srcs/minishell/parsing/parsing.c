/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:01:16 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/28 18:10:43 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_open(char *file, t_token token)
{
	if (token == INPUT)
		return (open(file, O_RDONLY));
	else if (token == OUTPUT)
		return (open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	else if (token == APPEND)
		return (open(file, O_CREAT | O_APPEND | O_WRONLY, 0644));
	return (-1);
}

bool	check_file(t_parsing *parsing, t_lexer *lexer)
{
	t_node	*node;
	char	*temp;
	char	*temp_cmd;

	node = NULL;
	node = lexer->head;
	while (node)
	{
		if (node->token == INPUT)
		{
			if (parsing->heredoc)
			{
				free(parsing->heredoc);
				parsing->heredoc = NULL;
			}
			if (parsing->input != -1)
				close(parsing->input);
			parsing->input = ft_open(node->name, INPUT);
			if (parsing->input == -1)
			{
				perror(node->name);
				return (false);
			}
		}
		else if (node->token == OUTPUT || node->token == APPEND)
		{
			if (parsing->output != -1)
				close(parsing->output);
			parsing->append = false;
			parsing->output = ft_open(node->name, node->token);
			if (node->token == APPEND)
				parsing->append = true;
			if (parsing->output == -1)
			{
				perror(node->name);
				return (false);
			}
		}
		else if (node->token == CMD)
		{
			temp = ft_strdup(node->name);
			if (!temp)
			{
				perror("Memory allocation error");
				return (false);
			}
			if (parsing->cmd == NULL)
				parsing->cmd = temp;
			else
			{
				temp_cmd = ft_strjoin(parsing->cmd, " ");
				if (!temp_cmd)
				{
					perror("Memory allocation error");
					free(temp);
					return (false);
				}
				parsing->cmd = ft_strjoin(temp_cmd, temp);
				free(temp);
				free(temp_cmd);
			}
		}
		else if (node->token == HEREDOC)
		{
			parsing->heredoc = ft_heredoc(node->name);
			if (!parsing->heredoc)
			{
				perror("Memory allocation error");
				return (false);
			}
			close(parsing->input);
			parsing->input = -1;
		}
		node = node->next;
	}
	return (true);
}

void	init_parsing(t_parsing *parsing)
{
	parsing->cmd = NULL;
	parsing->input = -1;
	parsing->output = -1;
	parsing->append = false;
    parsing->isbuiltins = false;
	parsing->heredoc = NULL;
	parsing->next = NULL;
}

t_parsing *ft_parsing(t_lexer *lexer)
{
    t_parsing *head = NULL;
    t_parsing *prev_parsing = NULL;

    if (!lexer)
        return NULL;
    while (lexer)
    {
        t_parsing *current_parsing = malloc(sizeof(t_parsing));
        if (!current_parsing)
            return (NULL);
        init_parsing(current_parsing);
        if (!check_file(current_parsing, lexer))
            return (NULL);
        if (isbuiltins(ft_split(current_parsing->cmd,  " ")[0]))
            current_parsing->isbuiltins = true;
        if (prev_parsing)
            prev_parsing->next = current_parsing;
        else
            head = current_parsing;
        prev_parsing = current_parsing;
        lexer = lexer->next;
    }
    return head;
}
