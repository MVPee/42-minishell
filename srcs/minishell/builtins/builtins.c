/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:06:36 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/06 09:55:23 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	isspecial(t_parsing parsing)
{
	int		i;

	char *split[] = {"unset", "cd", "exit", NULL};
	i = -1;
	while (split[++i])
		if (!ft_strcmp(split[i], parsing.cmd[0]))
			return (true);
	if (!ft_strcmp("export", parsing.cmd[0]) && parsing.cmd[1])
		return (true);
	return (false);
}

bool	isbuiltins(char *line)
{
	int		i;

	if (!line)
		return (false);
	char *split[] = {"echo", "pwd", "env", "unset", "export", "cd", "exit", NULL};
	i = -1;
	while (split[++i])
		if (!ft_strcmp(line, split[i]))
			return (true);
	return (false);
}

char	*builtins(t_env **head, t_data *data, t_parsing parsing)
{
	char	*result;
	char	buffer[500];

	if (!ft_strcmp(parsing.cmd[0], "echo"))
		ft_echo(data, parsing.cmd);
	else if (!ft_strcmp(parsing.cmd[0], "env"))
		ft_env(data, *head, parsing.cmd);
	else if (!ft_strcmp(parsing.cmd[0], "pwd"))
		ft_pwd(data, head);
	else if (!ft_strcmp(parsing.cmd[0], "unset"))
		ft_unset(head, data, parsing.cmd);
	else if (!ft_strcmp(parsing.cmd[0], "export"))
		ft_export(head, data, parsing.cmd);
	else if (!ft_strcmp(parsing.cmd[0], "cd"))
		ft_cd(*head, data, parsing.cmd);
	else if (!ft_strcmp(parsing.cmd[0], "exit"))
		ft_exit(*head, data, parsing.cmd);
	return (NULL);
}
