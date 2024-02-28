/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:18:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/28 18:23:26 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_lexer *lexer_parsing(char *str)
{
	char	**split;
	int		i;
	bool	flag;
	t_lexer	*cmd;
	t_node	*node;

	i = -1;
	split = ft_split(str, " ");
	cmd = ft_lexer_new(str);
	node = NULL;
	while (split[++i])
	{
		if (!ft_strcmp(split[i], "<<"))
			flag = ft_node_add(&node, ft_node_new(split[++i], HEREDOC));
		else if (!ft_strcmp(split[i], "<"))
			flag = ft_node_add(&node, ft_node_new(split[++i], INPUT));
		else if (!ft_strcmp(split[i], ">"))
			flag = ft_node_add(&node, ft_node_new(split[++i], OUTPUT));
		else if (!ft_strcmp(split[i], ">>"))
			flag = ft_node_add(&node, ft_node_new(split[++i], APPEND));
		else
			flag = ft_node_add(&node, ft_node_new(split[i], CMD));
		if (!flag)
			return (NULL);
	}
	cmd->head = node;
	return (cmd);
}

static bool check_after_pipe_and_semicolon(char *line)
{
	char **split;
	int i;

	split = ft_split(line, " ");
	i = -1;
	while(split[++i])
	{
		if (!ft_strcmp(split[i], ";"))
		{
			if (split[i + 1])
				return(ft_printf("syntax error near unexpected token '%s'\n", split[i + 1]), ft_free(1, &split), true);
			return (ft_free(1, &split), ft_printf("syntax error near unexpected token 'newline'\n"), true);
		}
		if (!ft_strcmp(split[i], "|") && !split[i + 1])
			return (ft_free(1, &split), ft_printf("syntax error near unexpected token 'newline'\n"), true);
	}
	return (false);
}

t_lexer	*ft_lexer(char *line, t_data *data)
{
	char	**split;
	int		i;
	t_lexer	*head = NULL;
	t_lexer	*lexer = NULL;

	if (check_after_pipe_and_semicolon(line))
		return (data->env_var = 2, NULL);
	if (!ft_strcmp(line, "\0"))
		return (NULL);
	i = -1;
	split = ft_split(line, "|");
	while (split[++i])
	{
		lexer = lexer_parsing(split[i]);
		if (!lexer)
			free_lexer(lexer);
		ft_lexer_add(&head, lexer);
	}
	return (head);
}
