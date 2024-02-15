/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:08:04 by nechaara          #+#    #+#             */
/*   Updated: 2024/02/15 17:18:20 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_env *head, t_data *data, char **split)
{
	char buffer[500];

	if (ft_splitlen((const char **)split) > 2)
	{
		ft_printf("%s: too many arguments\n", split[0]);
		data->env_var = 1;
		return ;
	}
	if (!split[1])
	{
		find_key(head, "OLDPWD")->value = ft_strdup(getcwd(buffer, 500));
		if (chdir(getenv("HOME")) != 0)
			perror(split[0]);
		else
			find_key(head, "PWD")->value = ft_strdup(getcwd(buffer, 500));
	}
	else if (!ft_strcmp(split[1], "-"))
	{
		char *temp = ft_strdup(getcwd(buffer, 500));
		if (!find_key(head, "OLDPWD"))
		{
			ft_printf("%s: OLDPWD not set\n", split[0]);
			return ;
		}
		if (chdir(find_key(head, "OLDPWD")->value) != 0)
			perror(split[0]);
		else
		{
			ft_printf("%s\n", find_key(head, "OLDPWD")->value);
			find_key(head, "OLDPWD")->value = ft_strdup(temp);
			ft_free(1, &temp);
			find_key(head, "PWD")->value = ft_strdup(getcwd(buffer, 500));
		}
	}
	else if (chdir(split[1]) != 0)
	{
		perror(split[1]);
		data->env_var = 1;
	}
}
