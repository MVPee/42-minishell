/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:01 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/14 11:09:54 by mvan-pee         ###   ########.fr       */
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

char *get_path(t_env *head)
{
	return (get_value(find_key(head, "PATH")));
}

char	*get_pwd(t_env *head)
{
	return (get_value(find_key(head, "PWD")));
}

void get_env(t_env *head)
{
	while(head->next)
	{
		ft_printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}