/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:01 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/15 15:14:17 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

size_t	get_size(t_env *head)
{
	size_t i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

t_env	*find_key(t_env *head, char *key)
{
	while (head)
	{
		if (!ft_strcmp(head->key, key))
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_env	*remove_top_node(t_env **head)
{
	t_env	*new_head;
	
	new_head = (*head)->next;
	ft_printf("NEW HEAD ADDRESS %x\n", new_head);
	if (new_head)
		new_head->prv = NULL;
	*head = new_head;
	return (new_head);
}
char	*get_value(t_env *target_node)
{
	if (target_node)
		return (target_node->value);
	return (NULL);
}

t_env	*get_last_entry(t_env **head)
{
	while ((*head)->next)
		*head = (*head)->next;
	return (*head);
}
