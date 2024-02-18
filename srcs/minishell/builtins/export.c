/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:48:51 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/19 00:21:24 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void display_export_list(t_env *head)
{
	if (!head)
		return ;
	while (head)
	{
		ft_printf("declare -x %s=%s\n",head->key, head->value);
		head = head->next;
	}
	ft_printf("declare -x _=/usr/bin/env\n");
}

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

static t_env	*ft_sorted_env(t_env *head)
{
	int		is_swapped;
	t_env	*traveling_node;

	is_swapped = 1;
	if (!head)
		return (NULL);
	while (is_swapped)
	{
		is_swapped = 0;
		traveling_node = head;
		while (traveling_node->next)
		{
			if (ft_strcmp(traveling_node->key, traveling_node->next->key) > 0)
			{
				swap_env_node(traveling_node, traveling_node->next);
				is_swapped = 1;
			}
			traveling_node = traveling_node->next;
		}
	}
	return (head);
}

void	ft_export(t_env *head, t_data *data, char *line)
{
	int i;
	char	**split;
	bool	do_concatenate;
	
	split = ft_export_split(line, &do_concatenate);
	if (ft_splitlen((const char **)split) == 1)
		display_export_list(ft_sorted_env(head));
	else
	{
		if (!split)
			return ;
		if (do_concatenate)
			write_value(head, split[0], split[1]);
		else
		{
			head = env_remove_entry(&head, split[0]);
			head = env_add_entry(head, split[1]);
		}
	}
	data->env_var = 0;
}
