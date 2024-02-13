/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:37:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/13 10:06:50 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

static void	extract_int(char *envs, t_env *env_vars)
{
	char **splitted_env;

	if (!ft_strncmp(envs, "SHLVL", 5))
	{
		splitted_env = ft_split(envs, "=");
		env_vars->shell_level = ft_atoi(splitted_env[1]);
		ft_free_matrix(1, &splitted_env);
	}	
}

static void	extract_str(char *envs, t_env *env_vars)
{
	char **splitted_env;

	if (!ft_strncmp(envs, "PWD", 3))
	{
		splitted_env = ft_split(envs, "=");
		env_vars->pwd = ft_strdup(splitted_env[1]);
		ft_free_matrix(1, &splitted_env);
	}
	else if(!ft_strncmp(envs, "PATH", 4))
	{
		env_vars->path = ft_split(envs, "=:");
	}
}

static t_env	ft_extract_env(char **envs)
{
	t_env	env_vars;
	
	while (*envs)
	{
		extract_int(*envs, &env_vars);
		extract_str(*envs, &env_vars);
		envs++;
	}
	return (env_vars);
}

static void env_init(t_env *env)
{
    env->path = NULL;
    env->pwd = NULL;
    env->shell_level = 0;
}

static char *get_str_readline(t_env env)
{
	char *temp = ft_strjoin(YELLOW BOLD, env.pwd);
    char *str_pwd = ft_strjoin(temp, RESET);
	char *str = ft_strjoin(RED BOLD "minihell " RESET, str_pwd);
	char *str_readline = ft_strjoin(str, ": ");
	return (ft_free(3, &str, &str_pwd, &temp), str_readline);
}

int main(int ac, char **argv, char **envs)
{
    char *line = NULL;
	t_env env;

    env_init(&env);
    env = ft_extract_env(envs);

    while (1)
    {
		char *str_readline = get_str_readline(env);
        line = readline(str_readline);
		ft_free(1, &str_readline);
        if (!ft_strcmp(line, "exit"))
        {
            free(line);
            break;
        }
    }
	ft_free(1, &env.pwd);
	ft_free_matrix(1, &env.path);
    return (0);
}
