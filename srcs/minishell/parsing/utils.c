/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:39:00 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/22 15:37:38 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_cmd	*ft_cmd_new(char *cmds)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_strdup(cmds);
    if (!cmd->cmd)
        return (NULL);
	cmd->head = NULL;
	cmd->next = NULL;
	cmd->pid = 0;
	return (cmd);
}

void	ft_cmd_add(t_cmd **head, t_cmd *new)
{
	t_cmd	*last;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

t_node	*ft_node_new(char *name, t_token token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->name = name;
	node->token = token;
	node->next = NULL;
	return (node);
}

void	ft_node_add(t_node **head, t_node *new)
{
	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		t_node *last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}
