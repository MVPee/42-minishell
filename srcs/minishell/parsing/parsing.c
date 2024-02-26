/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:01:16 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/26 17:18:03 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int ft_open(char *file, t_token token)
{
    if (token == INPUT)
        return (open(file, O_RDONLY));
    else if (token == OUTPUT)
        return (open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644));
    else if (token == APPEND)
        return (open(file, O_CREAT | O_APPEND | O_WRONLY, 0644));
    return (-1);
}

bool check_file(t_parsing *parsing, t_lexer *lexer)
{
    t_node *node = NULL;
    node = lexer->head;
    while(node)
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
                return false;
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
                return false;
            }
        }
        else if (node->token == CMD)
        {
            char *temp = ft_strdup(node->name);
            if (!temp)
            {
                perror("Memory allocation error");
                return false;
            }
            if (parsing->cmd == NULL)
                parsing->cmd = temp;
            else
            {

                char *temp_cmd = ft_strjoin(parsing->cmd, " ");
                if (!temp_cmd)
                {
                    perror("Memory allocation error");
                    free(temp);
                    return false;
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
                return false;
            }
            close(parsing->input);
            parsing->input = -1;
        }
        node = node->next;
    }
    return true;
}

void init_parsing(t_parsing *parsing)
{
    parsing->cmd = NULL;
    parsing->input = -1;
    parsing->output = -1;
    parsing->append = false;
    parsing->heredoc = NULL;
}

bool ft_parsing(t_parsing *parsing, t_lexer *lexer)
{
    if (!lexer)
        return false;
    init_parsing(parsing);
    if (!check_file(parsing, lexer))
        return false;
    free_lexer(lexer);
    return (true);
}
