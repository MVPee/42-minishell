/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:19:21 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/19 15:02:49 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**env_split(char *env)
{
	char	**result;
	char	*split;
	size_t	len;

	split = ft_strchr(env, '=');
	if (!split || split == env)
		return (NULL);
	len = split - env;
	result = (char **)malloc(3 * sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = ft_strndup(env, len);
	if (!result[0])
	{
		free(result);
		return (NULL);
	}
	result[1] = strdup(split + 1);
	result[2] = NULL;
	return (result);
}

static t_env	*create_node(char *entry)
{
	t_env	*created_node;
	char	**splitted_arguments;
	
	created_node = (t_env *)malloc(sizeof(t_env));
	if (!created_node)
		return (NULL);
	splitted_arguments = env_split(entry);
	if (!splitted_arguments)
		return (free(created_node), created_node = NULL, NULL);
	created_node->key = NULL;
	if (splitted_arguments[0])
		created_node->key = ft_strdup(splitted_arguments[0]);
	created_node->value = NULL;
	if (splitted_arguments[1])
	{
		if (!ft_strcmp(created_node->key, "SHLVL"))
			created_node->value = ft_itoa(ft_atoi(splitted_arguments[1]) + 1);
		else
			created_node->value = ft_strdup(splitted_arguments[1]);
	}
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

t_env	*env_remove_entry(t_env **head, char *key)
{
	t_env	*previous_entry;
	t_env	*current_entry;
	t_env	*next_entry;

	current_entry = find_key(*head, key);
	if (!current_entry)
		return (*head);
	if (*head == current_entry)
	{
		*head = current_entry->next;
		current_entry->prv = NULL;
		current_entry = NULL;
	}
	else
	{
		previous_entry = current_entry->prv;
		next_entry = current_entry->next;
		if (previous_entry)
			previous_entry->next = next_entry;
		if (next_entry)
			next_entry->prv = previous_entry;
	}
	free(current_entry);
	return (*head);
}

t_env	*env_init(char **envs)
{	
	t_env	*head;
	t_env	*tmp;
	int		i;

	head = NULL;
	i = 0;
	while (envs[i])
	{
		head = env_add_entry(head, envs[i]);
		i++;
	}
	if (find_key(head, "SHLVL") == NULL)
		head = env_add_entry(head, "SHLVL=0");
	else
	{
		tmp = find_key(head, "SHLVL");
		if (ft_atoi(tmp->value) >= 1000)
			tmp->value = ft_itoa(1);
	}
	return (head);
}
