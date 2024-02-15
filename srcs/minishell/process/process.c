/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:10:12 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/15 18:36:54 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*find_executable_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*temp;

	if (!paths)
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

void	process(t_env *head, t_data *data, char *line)
{
	int		status;
	char	**split;
	char	*path;
	pid_t	pid;

	split = ft_split(line, " ");
	path = find_executable_path(ft_split((const char *)get_value(find_key(head, "PATH")), ":"), split[0]);
    if (!path)
    {
        char buffer[500];
        path = ft_strjoin(getcwd(buffer, 500), ft_strtrim(line, ". "));
    }
	if (access(path, F_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(path, split, env_to_tab(head));
			perror(line);
		}
		else
        {
            if (waitpid(pid, &status, 0) == -1)
				perror("waitpid");
            if (WIFEXITED(status))
                data->env_var = WEXITSTATUS(status);
        }
	}
	else
	{
		perror(line);
		data->env_var = 127;
	}
}