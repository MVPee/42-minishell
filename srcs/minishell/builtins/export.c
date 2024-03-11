/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:48:51 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/11 17:29:41 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	add_env(t_env **head, char *key, char *value, bool append_content)
{
	char	*clean_entry;

	if (!key)
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
		if (key && value)
			clean_entry = reconstructed_entry(key, value);
		else
			clean_entry = ft_strdup(key);
		if (find_key(*head, key))
			env_remove_entry(head, key);
		env_entry_update(head, clean_entry);
		free(clean_entry);
	}
	ft_free(2, &key, &value);
}

static void	*add_null_content(t_env **head, char *key, t_data *data)
{
	if (!key)
		return (NULL);
	if (!is_key_valid(key))
	{
		(*data).env_var = UNSUCCESSFUL_COMMAND;
		return (non_valid_arg(key));
	}
	add_env(head, key, NULL, false);
	(*data).env_var = SUCCESSFUL_COMMAND;
	return (NULL);
}

static void	*add_content(t_env **head, char *line, t_data *data)
{
	char	*equal_address;
	char	*stop_location;
	bool	append_content;
	char	*value;
	char	*key;

	equal_address = ft_strchr(line, '=');
	if (!equal_address || line == equal_address)
	{
		(*data).env_var = UNSUCCESSFUL_COMMAND;
		return (non_valid_arg(line));
	}
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
	(*data).env_var = SUCCESSFUL_COMMAND;
	return (NULL);
}

void	ft_export(t_env **head, t_data *data, char **split)
{
	char	*temp;
	size_t	index;
	
	if (ft_splitlen((const char **)split) > 1)
	{
		index = 1;
		while (split[index])
		{
			if (ft_strchr(split[index], '=') == NULL)
				add_null_content(head, split[index++], data);
			else
				add_content(head, split[index++], data);
		}
	}
	else
		ft_sorted_env(*head);
}
