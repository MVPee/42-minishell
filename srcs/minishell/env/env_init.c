/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:19:21 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/13 21:44:19 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*create_node(char *entry)
{
	t_env	*created_node;
	char	**splitted_arguments;
	
	created_node = (t_env *)malloc(sizeof(t_env));
	if (!created_node)
		return (NULL);
	splitted_arguments = ft_split(entry, "=");
	if (!splitted_arguments)
		return (NULL);
	created_node->key = ft_strdup(splitted_arguments[0]);
	created_node->value = NULL;
	if (splitted_arguments[1])
		created_node->value = ft_strdup(splitted_arguments[1]);
	created_node->next = NULL;
	created_node->prv = NULL;
	ft_free_matrix(1, &splitted_arguments);
	return (created_node);
}

t_env	*env_add_entry(t_env *head, char *entry)
{
	t_env			*new_element;
	t_env			*current;

	new_element = create_node(entry);
	if (!new_element)
		return (NULL);
	if (!head)
		return (new_element);
	current = head;
	while (current->next)
		current = current->next;
	current->next = new_element;
	new_element->prv = current;
	return (head);
}

// void	env_remove_entry(t_env *head, char *key)
// {
// 	t_env	*previous_entry;
// 	t_env	*current_entry;
// 	t_env	*next_entry;
	
// 	current_entry = find_key(head, key);
// 	if (!current_entry)
// 		return ;
// 	previous_entry = current_entry->prv;
// 	next_entry = current_entry->next;
// 	previous_entry->next = next_entry;
// 	next_entry->prv = previous_entry;
// }

void	env_init(char **envs)
{	
	t_env	*head = NULL;
	
	int i = 0;
	while (envs[i])
	{
		head = env_add_entry(head, envs[i]);
		i++;
	}
	find_key(head, "PWD");
}

