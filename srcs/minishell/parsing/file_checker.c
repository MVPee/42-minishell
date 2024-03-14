/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:37:09 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/13 17:24:47 by nechaara         ###   ########.fr       */
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
	else if (token == HEREDOC)
		return (open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644));
	return (-1);
}

static bool	input_check(t_parsing *parsing, t_node *node, t_env *env, \
		t_data *data)
{
	if (parsing->input != -1)
		close(parsing->input);
	parsing->input = ft_open(node->name, node->token);
	if (parsing->input == -1)
	{
		if (node->token == INPUT)
		{
			perror(node->name);
			parsing->flag = true;
		}
		else
			return (ft_printf_fd(2, RED "CHMOD 777 .heredoc\n" RESET), false);
	}
	if (node->token == HEREDOC)
	{
		ft_heredoc(parsing->input, &node->name, env, data);
		close(parsing->input);
		parsing->input = open(".heredoc", O_RDONLY, 0644);
		if (parsing->input == -1)
			return (ft_printf_fd(2, RED "CHMOD 777 .heredoc\n" RESET), false);
	}
	if (data->env_var == COMMAND_INTERRUPTED)
		return (false);
	return (true);
}

static void	output_check(t_parsing *parsing, t_node *node)
{
	if (parsing->output != -1)
		close(parsing->output);
	parsing->output = ft_open(node->name, node->token);
	if (parsing->output == -1)
	{
		perror(node->name);
		parsing->flag = true;
	}
}

bool	file_checker(t_parsing *parsing, t_lexer lexer, t_env *env, \
		t_data *data)
{
	t_node	*node;

	node = NULL;
	node = lexer.head;
	while (node)
	{
		if (node->token == INPUT || node->token == HEREDOC)
			if (!input_check(parsing, node, env, data))
				return (false);
		if (node->token == OUTPUT || node->token == APPEND)
			output_check(parsing, node);
		node = node->next;
	}
	return (true);
}
