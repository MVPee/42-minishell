/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 13:37:37 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/06 09:56:15 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_env(t_data *data, t_env *head, char **split)
{
	char	*result;
	char	*temp;

	if (split[1])
	{
		ft_printf_fd(2, "env: '%s' No such file or directory\n", split[1]);
		data->env_var = 127;
	}
	else
	{
		while (head)
		{
			ft_printf("%s=%s\n", head->key, head->value);
			head = head->next;
		}
		ft_printf("_=/usr/bin/env\n");
		data->env_var = 0;
	}
}
