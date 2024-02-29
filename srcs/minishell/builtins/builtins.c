/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:06:36 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/28 18:43:52 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool isbuiltins(char *line)
{
	char *split[] = {"echo", "pwd", "env", "unset", "export", "cd", NULL};
	int i = -1;

	while(split[++i])
		if (!ft_strcmp(line, split[i]))
			return (true);
	return (false);
}

char *builtins(t_env **head, t_data *data, char *line, t_parsing *next)
{
	char	**split;
	char *temp;
	char *result;
	char buffer[500];

	char *check;

	temp = ft_strtrim(line, " ");
	if (!ft_strcmp(temp, "\0"))
		return (ft_free(1, &temp), NULL);
	split = ft_split(line, " ");
	if (!ft_strcmp(split[0], "echo"))
		return(ft_echo(data, split));
	else if (!ft_strcmp(split[0], "env"))
		return(ft_env(data, *head, split));
	else if (!ft_strcmp(split[0], "pwd"))
		return(ft_pwd(data, head));
	else if (!ft_strcmp(split[0], "unset"))
		return(ft_unset(head, data, line));
	else if (!ft_strcmp(split[0], "export"))
		 return(ft_export(*head, data, line));
	else if(!ft_strcmp(split[0], "cd"))
		check = ft_cd(*head, data, split, next);
	else if (!ft_strcmp(split[0], "exit"))
		ft_exit(*head ,data, line);
	else
		return (ft_free(1, &temp), ft_free_matrix(1, &split), NULL);

	ft_printf("%s", check);
	return (ft_free(1, &temp), ft_free_matrix(1, &split), NULL);
}
