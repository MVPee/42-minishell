/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:01 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/14 14:06:27 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

char	*get_value(t_env *head, char *key)
{
	t_env	*target_node;

	target_node = find_key(head, key);
	if (!target_node)
		return (NULL);
	return (target_node->value);
}

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