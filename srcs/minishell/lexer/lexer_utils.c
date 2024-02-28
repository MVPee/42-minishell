/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:39:00 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/28 16:21:39 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_lexer	*ft_lexer_new(char *cmd)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->cmd = ft_strdup(cmd);
    if (!lexer->cmd)
        return (NULL);
	lexer->head = NULL;
	lexer->next = NULL;
	lexer->pid = 0;
	return (lexer);
}

void	ft_lexer_add(t_lexer **head, t_lexer *new)
{
	t_lexer	*last;

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

	if (!name)
			return (ft_printf("syntax error near unexpected token '%d'\n", token), NULL);
	if (!ft_strcmp(name, "<") || !ft_strcmp(name, ">") || !ft_strcmp(name, "<<") || !ft_strcmp(name, ">>") || name[0] == '|')
		return (ft_printf("syntax error near unexpected token '%s'\n", name), NULL);
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->name = name;
	node->token = token;
	node->next = NULL;
	return (node);
}

bool	ft_node_add(t_node **head, t_node *new)
{
	if (!head || !new)
		return false;
	if (!*head)
		*head = new;
	else
	{
		t_node *last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return true;
}

void free_lexer(t_lexer *lexer) {
    t_lexer *lexer_current;
    t_node *node_current;

    while (lexer) {
        lexer_current = lexer;
        lexer = lexer->next;
        while (lexer_current->head) {
            node_current = lexer_current->head;
            lexer_current->head = lexer_current->head->next;
            free(node_current->name);
            free(node_current);
        }
        free(lexer_current->cmd);
        free(lexer_current);
    }
}
