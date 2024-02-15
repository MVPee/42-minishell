/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:48:51 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/15 13:04:04 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_export(t_env *head, t_data *data, char **split)
{
	int i;

	if (ft_splitlen((const char **)split) == 1)
	{
		// Temporaire
		while (head)
		{
			ft_printf("declare -x %s=%s\n", head->key, head->value);
			head = head->next;
		}
		ft_printf("declare -x _=/usr/bin/env\n");
	}
	else
	{
		i = 1;
		while (split[i])
		{
			head = env_add_entry(head, split[i]);
			i++;
		}
	}
	data->env_var = 0;
}