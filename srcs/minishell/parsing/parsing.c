/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:18:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/19 17:27:16 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	add_node_to_cmd(t_node **head, char *name, char *token)
{
	t_node	*new_node;
	t_node	*current;

    if (name == NULL)
    {
        ft_printf("syntax error near unexpected token '%s'\n", token);
        return ;
    }
	new_node = malloc(sizeof(t_node));
	new_node->name = name;
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

static void	init_struct(t_cmd **cmd)
{
	(*cmd)->cmd = NULL;
    (*cmd)->pid = 0;
	(*cmd)->input = NULL;
	(*cmd)->output = NULL;
	(*cmd)->append = NULL;
	(*cmd)->heredoc = NULL;
	(*cmd)->next = NULL;
	(*cmd)->prv = NULL;
}

static t_cmd	*check_cmd(char *str)
{
	int		i;
	char	**split;
	char	*cmds;
	char	*temp;
	t_cmd	*tmp;

	i = -1;
	split = ft_split(str, " ");
	cmds = ft_strdup("");
	tmp = malloc(sizeof(t_cmd));
	init_struct(&tmp);
	while (split[++i])
	{
		if (!ft_strcmp(split[i], "<<"))
            add_node_to_cmd(&(tmp->heredoc), split[++i], "<<");
		else if (!ft_strcmp(split[i], "<"))
			add_node_to_cmd(&(tmp->input), split[++i], "<");
        else if (!ft_strcmp(split[i], ">"))
			add_node_to_cmd(&(tmp->output), split[++i], ">");
        else if (!ft_strcmp(split[i], ">>"))
			add_node_to_cmd(&(tmp->append), split[++i], ">>");
        else
		{
			temp = ft_strjoin(cmds, split[i]);
			cmds = ft_strjoin(temp, " ");
			free(temp);
		}
        if (!split[i])
            break;
	}
	tmp->cmd = cmds;
	return (tmp);
}

t_cmd	*parsing(char *line)
{
	char	**split;
	int		i;
	t_cmd	*head;
	t_cmd	*current_cmd;
	t_cmd	*new_cmd;

	head = NULL;
	current_cmd = NULL;
	new_cmd = NULL;
	split = ft_split(line, "|");
	i = -1;
	while (split[++i])
	{
		new_cmd = check_cmd(split[i]);
		if (current_cmd == NULL)
		{
			current_cmd = new_cmd;
			head = current_cmd;
		}
		else
		{
			current_cmd->next = new_cmd;
			new_cmd->prv = current_cmd;
			current_cmd = current_cmd->next;
		}
	}
	return (head);
}
