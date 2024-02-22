/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:18:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/22 15:37:48 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_cmd	*check_cmd(char *str)
{
	char	**split;
	int		i;
	t_cmd	*cmd;
	t_node	*node_head;
	t_node	*node;
	i = -1;
	split = ft_split(str, " ");
	cmd = ft_cmd_new(str);
	node_head = NULL;
	while (split[++i])
	{
		if (!ft_strcmp(split[i], "<<"))
		{
			i++;
			ft_node_add(&node_head, ft_node_new(split[i], HEREDOC));
		}
		else if (!ft_strcmp(split[i], "<"))
		{
			i++;
			ft_node_add(&node_head, ft_node_new(split[i], INPUT));
		}
		else if (!ft_strcmp(split[i], ">"))
		{
			i++;
			ft_node_add(&node_head, ft_node_new(split[i], OUTPUT));
		}
		else if (!ft_strcmp(split[i], ">>"))
		{
			i++;
			ft_node_add(&node_head, ft_node_new(split[i], APPEND));
		}
		else
			ft_node_add(&node_head, ft_node_new(split[i], CMD));
	}
	cmd->head = node_head;
	return (cmd);
}

t_cmd	*parsing(char *line)
{
	char	**split;
	int		i;
	t_cmd	*head;
	t_cmd	*cmd;

	i = -1;
	head = NULL;
	split = ft_split(line, "|");
	while (split[++i])
	{
		cmd = check_cmd(split[i]);
		ft_cmd_add(&head, cmd);
	}
	return (head);
}
