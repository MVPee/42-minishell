/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:01 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/06 23:20:16 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

size_t	get_size(t_env *head)
{
	size_t	i;

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
	if (!key)
		return (NULL);
	while (head)
	{
		if (!ft_strcmp(head->key, key))
			return (head);
		head = head->next;
	}
	return (NULL);
}

char	*get_value(t_env *target_node)
{
	if (target_node)
		return (target_node->value);
	return (NULL);
}

void	write_value(t_env **head, char *key, char *value)
{
	t_env	*target_node;
	char	*initial_string;
	char	*string_to_join;

	target_node = find_key(*head, key);
	if (!target_node || !value)
		return ;
	initial_string = target_node->value;
	string_to_join = no_null_join(initial_string, value);
	free(initial_string);
	target_node->value = string_to_join;
}

t_env	*get_last_entry(t_env **head)
{
	while ((*head)->next)
		*head = (*head)->next;
	return (*head);
}
