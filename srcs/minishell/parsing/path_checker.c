/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:16:24 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/07 23:09:02 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*find_executable_path(char **paths, t_parsing parsing)
{
	int		i;
	char	*path;
	char	*temp;

	if (!parsing.cmd)
		return (NULL);
	if (!paths)
		return (NULL);
	if (parsing.cmd[0][0] == '.' && parsing.cmd[0][1] == '/')
		return (ft_free_matrix(1, &paths), NULL);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (ft_free_matrix(1, &paths), NULL);
		path = ft_strjoin(temp, parsing.cmd[0]);
		if (!path)
			return (ft_free_matrix(1, &paths), ft_free(1, &temp), NULL);
		if (access(path, F_OK) == 0)
			return (ft_free_matrix(1, &paths), ft_free(1, &temp), path);
		ft_free(2, &path, &temp);
	}
	return (ft_free_matrix(1, &paths), NULL);
}

char	*path_checker(char **paths, t_parsing parsing)
{
	char	*path;
	char	*temp;
	char	buffer[500];

	if (access(parsing.cmd[0], F_OK) == 0)
		return (ft_strdup(parsing.cmd[0]));
	path = find_executable_path(paths, parsing);
	if (!path)
	{
		temp = ft_strtrim(parsing.cmd[0], ". ");
		if (!temp)
			return (NULL);
		path = ft_strjoin(getcwd(buffer, 500), temp);
		ft_free(1, &temp);
	}
	if (!path)
		return (NULL);
	if (access(path, F_OK) == 0)
		return (path);
	return (free(path), NULL);
}
