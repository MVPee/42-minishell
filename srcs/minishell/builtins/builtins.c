/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:06:36 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/15 14:59:07 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	builtins(t_env *head, t_data *data, char *line)
{
	char	**split;

	if (line[0] == '\0')
		return (true);
	split = ft_split(line, " ");
	if (!ft_strcmp(split[0], "echo"))
		ft_echo(data, split);
	else if (!ft_strcmp(split[0], "env"))
		ft_env(data, head, split);
	else if (!ft_strcmp(split[0], "pwd"))
		ft_pwd(data, head);
	else if (!ft_strcmp(split[0], "unset"))
		ft_unset(head, data, split);
	else if (!ft_strcmp(split[0], "export"))
		ft_export(head, data, split);
	else if(!ft_strcmp(split[0], "cd"))
		ft_cd(head, data, split);
	else
		return (ft_free_matrix(1, &split), false);
	return (ft_free_matrix(1, &split), true);
}
