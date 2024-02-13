/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:37:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/13 13:50:18 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

static void	env_init(t_env *env, char **envs)
{
	env->path = NULL;
	env->pwd = NULL;
	env->shell_level = 0;
	env->var_env = 0;
	env->env = ft_splitdup((const char **)envs);
}

static t_env	ft_extract_env(char **envs)
{
	t_env	env_data;
	char	**splitted_env;

	env_init(&env_data, envs);
	while (*envs)
	{
		if (!ft_strncmp(*envs, "PWD", 3))
		{
			splitted_env = ft_split(*envs, "=");
			env_data.pwd = ft_strdup(splitted_env[1]);
			ft_free_matrix(1, &splitted_env);
		}
		else if (!ft_strncmp(*envs, "PATH", 4))
		{
			env_data.path = ft_split(*envs, "=:");
		}
		else if (!ft_strncmp(*envs, "SHLVL", 5))
		{
			splitted_env = ft_split(*envs, "=");
			env_data.shell_level = ft_atoi(splitted_env[1]);
			ft_free_matrix(1, &splitted_env);
		}
		envs++;
	}
	return (env_data);
}

static char	*get_str_readline(t_env env)
{
	char	*temp;
	char	*str_pwd;
	char	*str_readline;

	temp = ft_strjoin(YELLOW BOLD, env.pwd);
	str_pwd = ft_strjoin(temp, RESET);
	ft_free(1, &temp);
	temp = ft_strjoin(RED BOLD "minihell " RESET, str_pwd);
	str_readline = ft_strjoin(temp, ": ");
	ft_free(2, &str_pwd, &temp);
	return (str_readline);
}

static void process(t_env env, char *line)
{
	char **split = ft_split(line, " ");
	if (!ft_strcmp(split[0], "echo"))
		ft_echo(env, split);
	else if (!ft_strcmp(split[0], "env"))
		ft_env(env, split);
	else
		ft_printf("%s: command not found\n", line);
	ft_free_matrix(1, &split);
}

int	main(int ac, char **argv, char **envs)
{
	char	*line;
	t_env	env;
	char	*str_readline;

	line = NULL;
	env = ft_extract_env(envs);
	while (1)
	{
		str_readline = get_str_readline(env);
		line = readline(str_readline);
		ft_free(1, &str_readline);
		if (!ft_strcmp(line, "exit"))
		{
			free(line);
			break ;
		}
		process(env, line);
		free(line);
	}
	ft_free(1, &env.pwd);
	ft_free_matrix(2, &env.path, &env.env);
	return (0);
}
