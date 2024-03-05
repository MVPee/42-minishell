/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:48:51 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/05 13:36:39 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	add_env(t_env *head, char *key, char *value, bool append_content)
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
		write_value(&head, key, value);
	else
	{
		if (key && value)
			clean_entry = reconstructed_entry(key, value);
		else
			clean_entry = ft_strdup(key);
		if (find_key(head, key))
			env_remove_entry(&head, key);
		env_add_entry(head, clean_entry);
		free(clean_entry);
	}
	ft_free(2, &key, &value);
}

static void	*add_null_content(t_env *head, char *key)
{
	if (!head || !key)
		return (NULL);
	add_env(head, key, NULL, false);
}

static void	*add_content(t_env *head, char *line)
{
	char	*equal_address;
	char	*stop_location;
	bool	append_content;
	char	*value;
	char	*key;

	equal_address = ft_strchr(line, '=');
	if (!equal_address)
		return (NULL);
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
	return (NULL);
}

void	ft_export(t_env **head, t_data *data, char **split)
{
	char	*temp;
	size_t	index;

	ft_putsplit(split, "RESULT:");
	if (ft_splitlen((const char **)split) > 1)
	{
		index = 1;
		while (split[index])
		{
			if (ft_strchr(split[index], '=') == NULL)
				add_null_content(*head, split[index++]);
			else
				add_content(*head, split[index++]);
		}
	}
	ft_sorted_env(*head);
	data->env_var = 0;
}
