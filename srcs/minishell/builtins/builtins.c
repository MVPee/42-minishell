/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:06:36 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/05 13:36:08 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	isbuiltins(char *line)
{
	char	**result;
	char	*str;
	int		i;

	if (!line)
		return (false);
	result = ft_split(line, " ");
	str = ft_strdup(result[0]);
	char *split[] = {"echo", "pwd", "env", "unset", "export", "cd", "exit", \
		NULL};
	i = -1;
	while (split[++i])
		if (!ft_strcmp(str, split[i]))
			return (ft_free_matrix(1, &result), ft_free(1, &str), true);
	return (ft_free_matrix(1, &result), ft_free(1, &str), false);
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
