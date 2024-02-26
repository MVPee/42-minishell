/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:48:51 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/24 20:13:01 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void add_env(t_env *head, char *key, char *value, bool append_content)
{
	char	*clean_entry;
	
	if (!head || !key)
		return ;
	if (!is_key_valid(key))
	{
		error_handler_export(key, value);
		ft_free(2, &key, &value);
		return ;
	}
	if (append_content)
		write_value(head, key, value);
	else
	{
		clean_entry = reconstructed_entry(key, value);
		if (find_key(head, key))
			env_remove_entry(&head, key);
		env_add_entry(head, clean_entry);
		free(clean_entry);
	}
	ft_free(2, &key, &value);
}

static void *add_content(t_env *head, char *line)
{
	char	*equal_address;
	char	*stop_location;
	bool	append_content;
	char	*value;
	char	*key;

	equal_address = ft_strchr(line, '=');
	if (!equal_address)
		return (error_arguments_without_equal(line));
	else if (equal_address == line)	
		return (error_arguments_without_equal(line));
	append_content = (*(equal_address - 1) == '+');
	if (append_content)
		stop_location = equal_address - 1;
	else
		stop_location = equal_address;
	key = ft_strndup(line, stop_location - line);
	if (!key)
		return (NULL);
	value = ft_strdup(equal_address + 1);
	add_env(head, key, value, append_content);
}

void	ft_export(t_env *head, t_data *data, char *line)
{
	char	**splitted_args;
	size_t	index;

	
	splitted_args = ft_split(line, " ");
	if (!splitted_args)
		return ;
	if (ft_splitlen((const char **) splitted_args) > 1)
	{
		index = 1;
		while (splitted_args[index])
			add_content(head, splitted_args[index++]);
	}
	else 
		ft_sorted_env(head);
	ft_free_matrix(1, &splitted_args);
	data->env_var = 0;
}
