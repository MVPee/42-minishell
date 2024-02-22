/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:18:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/22 16:37:37 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_cmd *cmd_parsing(char *str)
{
	char	**split;
	int		i;
	t_cmd	*cmd;
	t_node	*node;

	i = -1;
	split = ft_split(str, " ");
	cmd = ft_cmd_new(str);
	node = NULL;
	while (split[++i])
	{
		if (!ft_strcmp(split[i], "<<"))
			ft_node_add(&node, ft_node_new(split[++i], HEREDOC));
		else if (!ft_strcmp(split[i], "<"))
			ft_node_add(&node, ft_node_new(split[++i], INPUT));
		else if (!ft_strcmp(split[i], ">"))
			ft_node_add(&node, ft_node_new(split[++i], OUTPUT));
		else if (!ft_strcmp(split[i], ">>"))
			ft_node_add(&node, ft_node_new(split[++i], APPEND));
		else
			ft_node_add(&node, ft_node_new(split[i], CMD));
	}
	cmd->head = node;
	return (cmd);
}

t_cmd	*parsing(char *line)
{
	char	**split;
	int		i;
	t_cmd	*head;
	t_cmd	*cmd;

	if (!ft_strcmp(line, "\0"))
		return (NULL);
	i = -1;
	head = NULL;
	split = ft_split(line, "|");
	while (split[++i])
	{
		cmd = cmd_parsing(split[i]);
		ft_cmd_add(&head, cmd);
	}
	return (head);
}
