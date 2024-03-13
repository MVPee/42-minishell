/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:06:36 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/13 11:23:05 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	ft_isspecial(t_parsing parsing)
{
	if (!ft_strcmp("unset", parsing.cmd[0]) || !ft_strcmp("cd", parsing.cmd[0])
		|| !ft_strcmp("exit", parsing.cmd[0]))
		return (true);
	if (!ft_strcmp("export", parsing.cmd[0]) && parsing.cmd[1])
		return (true);
	return (false);
}

bool	isbuiltins(char *line)
{
	if (!line)
		return (false);
	if (!ft_strcmp("echo", line) || !ft_strcmp("pwd", line) \
		|| !ft_strcmp("env", line) || !ft_strcmp("unset", line) \
		|| !ft_strcmp("export", line) || !ft_strcmp("cd", line) \
		|| !ft_strcmp("exit", line))
		return (true);
	return (false);
}

char	*builtins(t_env **head, t_data *data, t_parsing parsing)
{
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
