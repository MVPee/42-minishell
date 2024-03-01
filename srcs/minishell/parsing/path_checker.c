/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:16:24 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/01 18:58:25 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*find_executable_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*temp;

	if (!paths || !cmd)
		return (NULL);
	if (cmd[0] == '.' && cmd[1] == '/')
		return (ft_free_matrix(1, &paths), NULL);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (ft_free_matrix(1, &paths), NULL);
		path = ft_strjoin(temp, cmd);
		if (!path)
			return (ft_free_matrix(1, &paths), ft_free(1, &temp), NULL);
		if (access(path, F_OK) == 0)
			return (ft_free_matrix(1, &paths), ft_free(1, &temp), path);
		ft_free(2, &path, &temp);
	}
	ft_free_matrix(1, &paths);
	return (NULL);
}

char *path_checker(char **paths, char *cmd)
{
    char *path;
    char buffer[500];

    path = find_executable_path(paths, cmd);
    if (!path)
		path = ft_strjoin(getcwd(buffer, 500), ft_strtrim(cmd, ". "));
    if (access(path, F_OK) == 0)
        return (path);
    return (NULL);
}