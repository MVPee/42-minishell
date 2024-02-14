/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:01 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/14 20:54:33 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*get_value(t_env *target_node)
{
	if (target_node)
		return (target_node->value);
	return (NULL);
}

char *get_path(t_env *head)
{
	return (get_value(find_key(head, "PATH")));
}

void get_env(t_env *head)
{
	while(head)
	{
		ft_printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}
