/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:37:09 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/08 19:00:50 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_open(char *file, t_token token)
{
	if (token == INPUT)
		return (open(file, O_RDONLY));
	else if (token == OUTPUT)
		return (open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	else if (token == APPEND)
		return (open(file, O_CREAT | O_APPEND | O_WRONLY, 0644));
	return (-1);
}

static bool	input_check(t_parsing *parsing, t_node *node)
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
	return (true);
}

static bool	output_check(t_parsing *parsing, t_node *node)
{
	if (parsing->output != -1)
		close(parsing->output);
	parsing->output = ft_open(node->name, node->token);
	if (parsing->output == -1)
	{
		perror(node->name);
		return (false);
	}
	return (true);
}

static bool	heredoc_check(t_parsing *parsing, t_node *node, t_env *env, \
		t_data data)
{
	parsing->heredoc = ft_heredoc(&node->name, env, data);
	if (!parsing->heredoc)
	{
		parsing->heredoc = ft_strdup("");
		if (!parsing->heredoc)
		{
			ft_printf_fd(2, "Malloc failed: heredoc\n");
			return (false);
		}
	}
	parsing->input = -1;
	return (true);
}

bool	file_checker(t_parsing *parsing, t_lexer lexer, t_env *env, t_data data)
{
	t_node	*node;
	char	*temp;
	char	*temp_cmd;

	node = NULL;
	node = lexer.head;
	while (node)
	{
		if (node->token == INPUT)
			if (!input_check(parsing, node))
				return (false);
		if (node->token == OUTPUT || node->token == APPEND)
			if (!output_check(parsing, node))
				return (false);
		if (node->token == HEREDOC)
			if (!heredoc_check(parsing, node, env, data))
				return (false);
		node = node->next;
	}
	return (true);
}
