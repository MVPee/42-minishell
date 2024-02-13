/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:23:01 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/13 16:27:50 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_key(t_env *head, char *key)
{
	while (head)
	{
		if (!ft_strcmp(head->key, key))
		{
			printf("%s = %s\n", head->key, head->value);
		}
		head = head->next;
	}
	return (NULL);
}

static	char	*get_value(t_env *target_node)
{
	return (target_node->value);
}

char	*get_pwd(t_env *head)
{
	return (get_value(find_key(head, "PWD")));
}