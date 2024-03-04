/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:06:36 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/04 03:28:28 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool isbuiltins(char *line)
{
	if (!line)
		return false;
	char **result = ft_split(line, " ");
	char *str = ft_strdup(result[0]);
	char *split[] = {"echo", "pwd", "env", "unset", "export", "cd", "exit", NULL};
	int i = -1;

	while(split[++i])
		if (!ft_strcmp(str, split[i]))
			return (ft_free_matrix(1, &result), ft_free(1, &str), true);
	return (ft_free_matrix(1, &result), ft_free(1, &str), false);
}

char *builtins(t_env **head, t_data *data, t_parsing parsing)
{
	char *result;
	char buffer[500];

	if (!ft_strcmp(parsing.cmd_args[0], "echo"))
		ft_echo(data, parsing.cmd_args);
	else if (!ft_strcmp(parsing.cmd_args[0], "env"))
		ft_env(data, *head, parsing.cmd_args);
	else if (!ft_strcmp(parsing.cmd_args[0], "pwd"))
		ft_pwd(data, head);
	else if (!ft_strcmp(parsing.cmd_args[0], "unset"))
		ft_unset(head, data, parsing.cmd);
	else if (!ft_strcmp(parsing.cmd_args[0], "export"))
		ft_export(head, data, parsing.cmd_args);
	else if(!ft_strcmp(parsing.cmd_args[0], "cd"))
		ft_cd(*head, data, parsing.cmd_args);
	else if (!ft_strcmp(parsing.cmd_args[0], "exit"))
		ft_exit(*head, data, parsing.cmd_args);	
	return (NULL);
}
