/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:48:51 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/20 16:38:20 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	char *entry_only(char **split)
{
	char	*joined_string;
	
	joined_string = NULL;
	if (!split)
		return (NULL);
	joined_string = ft_strjoin(split[0], "=");
	joined_string = ft_strjoin(joined_string, split[1]);
	return (joined_string);
}

void	ft_export(t_env *head, t_data *data, char *line)
{
	int i;
	char	**split;
	bool	do_concatenate;
	bool	single_cmd;

	split = export_split(line, &do_concatenate, &single_cmd);
	if (single_cmd)
		ft_sorted_env(head);
	else
	{
		if (do_concatenate)
			write_value(head, split[0], split[1]);
		else
		{
			if (find_key(head, split[0]))
				env_remove_entry(&head, split[0]);
			head = env_add_entry(head, entry_only(split));
		}
	}
	data->env_var = 0;
}
