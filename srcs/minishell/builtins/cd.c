/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:08:04 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/15 16:18:46 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_env *head, t_data *data, char **split)
{
	if (ft_splitlen((const char **)split) > 2)
	{
		ft_printf("%s: too many arguments\n", split[0]);
		data->env_var = 1;
		return ;
	}
	if (!split[1])
	{
		if (chdir(getenv("HOME")) != 0)
			perror(split[0]);
	}
	else if (chdir(split[1]) != 0)
	{
		perror(split[1]);
		data->env_var = 1;
	}
}
