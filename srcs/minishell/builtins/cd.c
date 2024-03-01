/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:08:04 by nechaara          #+#    #+#             */
/*   Updated: 2024/03/01 19:27:53 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_cd_others(t_env *head, char **split)
{
	char	buffer[500];

	if (chdir(split[1]) != 0)
		return (perror(split[1]), 1);
	if (find_key(head, "OLDPWD"))
		find_key(head, "OLDPWD")->value = find_key(head, "PWD")->value;
	if (find_key(head, "PWD"))
		find_key(head, "PWD")->value = ft_strdup(getcwd(buffer, 500));
	return (0);
}

static int	ft_cd_with_minus(t_env *head, char **split)
{
	char	buffer[500];
	char	*temp;

	temp = ft_strdup(getcwd(buffer, 500));
	if (!find_key(head, "OLDPWD"))
	{
		ft_printf("%s: OLDPWD not set\n", split[0]);
		return (ft_free(1, &temp), 1);
	}
	if (chdir(find_key(head, "OLDPWD")->value) != 0)
		return (perror(split[0]), 1);
	if (find_key(head, "OLDPWD"))
	{
		ft_printf("%s\n", find_key(head, "OLDPWD")->value);
		find_key(head, "OLDPWD")->value = ft_strdup(temp);
	}
	if (find_key(head, "PWD"))
		find_key(head, "PWD")->value = ft_strdup(getcwd(buffer, 500));
	return (ft_free(1, &temp), 0);
}

static int	ft_cd_with_no_arguments(t_env *head, char **split)
{
	char	buffer[500];
	char	*temp;

	temp = ft_strdup(getcwd(buffer, 500));
	if (find_key(head, "HOME"))
		if (chdir(find_key(head, "HOME")->value) != 0)
			return (perror(split[0]), 1);
	if (find_key(head, "OLDPWD"))
		find_key(head, "OLDPWD")->value = ft_strdup(temp);
	if (find_key(head, "PWD"))
		find_key(head, "PWD")->value = ft_strdup(getcwd(buffer, 500));
	return (ft_free(1, &temp), 0);
}

void	ft_cd(t_env *head, t_data *data, char **split)
{
	
	char	buffer[500];
	char	*temp;

	data->env_var = 0;
	if (ft_splitlen((const char **)split) > 2)
	{
		ft_printf("%s: too many arguments\n", split[0]);
		data->env_var = 1;
	}
	else if (!split[1])
		data->env_var = ft_cd_with_no_arguments(head, split);
	else if (!ft_strcmp(split[1], "-"))
		data->env_var = ft_cd_with_minus(head, split);
	else
		data->env_var = ft_cd_others(head, split);
}
