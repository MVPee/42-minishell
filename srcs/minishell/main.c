/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:37:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/14 14:23:43 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

static char	*get_str_readline(t_env *head)
{
	(void)head;
	char	*temp;
	char	*str_pwd;
	char	*str_readline;

	temp = ft_strjoin(YELLOW BOLD, get_pwd(head));
	str_pwd = ft_strjoin(temp, RESET);
	ft_free(1, &temp);
	temp = ft_strjoin(RED BOLD "minihell " RESET, str_pwd);
	str_readline = ft_strjoin(temp, ": ");
	ft_free(2, &str_pwd, &temp);
	return (str_readline);
}

static bool builtins(t_env *head, t_data *data, char *line)
{
	if (line[0] == '\0')
		return true;
	char **split = ft_split(line, " ");
	if (!ft_strcmp(split[0], "echo"))
		ft_echo(data, split);
	else if (!ft_strcmp(split[0], "env"))
		ft_env(data, head, split);
	else if (!ft_strcmp(split[0], "pwd"))
		ft_pwd(data, head);
	else if (!ft_strcmp(split[0], "unset"))
		ft_unset(head, data, split);
	// else if(!ft_strcmp(split[0], "cd"))
	// 	ft_cd(env, split);
	else
	{
		ft_free_matrix(1, &split);
		return false;
	}
	ft_free_matrix(1, &split);
	return true;
}

static char	*find_executable_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*temp;

	if (!paths)
		return (NULL);
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

static void process(t_env *head, t_data *data, char *line, char **envs)
{
	int status;
	char **split = ft_split(line, " ");
	char *path = find_executable_path(ft_split((const char *)get_path(head), ":"), split[0]);
	if (path)
	{
		pid_t pid = fork();
		if (pid == 0)
			execve(path, split, envs);
		else
			waitpid(pid, &status, 0);
	}
	else
		ft_printf("%s: No such file or directory\n", line);
}

int	main(int ac, char **argv, char **envs)
{
	t_env *head;
	t_data data;
	char	*line;
	char	*str_readline;

	data.env_var = 0;
	head = env_init(envs);
	line = NULL;
	while (1)
	{
		str_readline = get_str_readline(head);
		line = readline(str_readline);
		ft_free(1, &str_readline);
		if (!ft_strcmp(line, "exit"))
		{
			ft_free(1, &line);
			break ;
		}
		if (!builtins(head, &data, line))
			process(head, &data, line, envs);
		ft_free(1, &line);
	}
	return (0);
}
