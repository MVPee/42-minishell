/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:01 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/14 10:33:37 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*get_value(t_env *target_node)
{
	return (target_node->value);
}

char	*get_pwd(t_env *head)
{
	return (get_value(find_key(head, "PWD")));
}