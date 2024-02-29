/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:12:03 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/28 17:22:29 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	swap_env_node(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

static t_env *copy_env_list(t_env *head) 
{
	t_env	*new_head;
	t_env	*prev;
	t_env	*new_node;

	new_head = NULL;
	prev = NULL;
	new_node = NULL;
	while (head) 
	{
		new_node = (t_env *)malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->key = ft_strdup(head->key);
		new_node->value = ft_strdup(head->value);
		new_node->next = NULL;
		
		if (prev) 
			prev->next = new_node;
		else
			new_head = new_node;
		prev = new_node;
		head = head->next;
	}
	return (new_head);
}

static void sort_env_list(t_env *head)
{
	int		swapped;
	t_env	*traveling_node;

	if (!head)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		traveling_node = head;
		while (traveling_node->next)
		{
			if (ft_strcmp(traveling_node->key, traveling_node->next->key) > 0)
			{
				swap_env_node(traveling_node, traveling_node->next);
				swapped = 1;
			}
			traveling_node = traveling_node->next;
		}
	}
}

static char  *print_and_return_sorted_env(t_env *head) 
{
	char *output;
	
	output = ft_strdup("");
	if (!output)
		return (NULL);
	while (head) 
	{
		output = ft_strjoin(output, ft_multi_strjoin(5, "declare -x ", head->key, "=\"", head->value, "\"\n"));
		head = head->next;
	}
	output = ft_strjoin(output, "declare -x _=/usr/bin/env\n\0");
	//ft_printf("%s", output);
	return (output);
}

char	*ft_sorted_env(t_env *head)
{
	t_env	*copy_of_env;
	char	*output;

	copy_of_env = copy_env_list(head);
	sort_env_list(copy_of_env);
	output = print_and_return_sorted_env(copy_of_env);
	free_env_list(copy_of_env);
	return (output);
}