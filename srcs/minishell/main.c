/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:37:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/12 19:11:35 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

static void	extract_int(char *env, t_env *env_vars, char **splitted_env)
{
	if (!ft_strncmp(env, "SHLVL", 5))
	{
		splitted_env = ft_split(env, "=");
		env_vars->shell_level = ft_atoi(splitted_env[1]);
		ft_free_matrix(1, &splitted_env);
	}	
}

static void	extract_str(char *env, t_env *env_vars, char **splitted_env)
{
	if (!ft_strncmp(env, "PWD", 3))
	{
		splitted_env = ft_split(env, "=");
		env_vars->pwd = splitted_env[1];
		ft_free_matrix(1, &splitted_env);
	}
	else if(!ft_strncmp(env, "PATH", 4))
	{
		env_vars->path = ft_split(env, "=:");
	}
}

static t_env	ft_extract_env(char **env)
{
	char	**splitted_env;
	t_env	env_vars;
	
	env_vars.pwd = NULL;
	while (*env)
	{
		extract_int(*env, &env_vars, splitted_env);
		extract_str(*env, &env_vars, splitted_env);
		env++;
	}
	return (env_vars);
}

static void env_init(t_env *env)
{
    env->path = NULL;
    env->pwd = NULL;
    env->shell_level = 0;
}

int main(int ac, char **argv, char **envs)
{
    char *line = NULL;
	t_env env;

    env_init(&env);
    env = ft_extract_env(envs);

    ft_printf("shlevel: %d\n", env.shell_level);
    ft_printf("pwd: %s\n", env.pwd);
    ft_printf("path0: %s\n", env.path[0]);
    while (777)
    {
        line = readline("minihell: ");
        if (ft_strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }
    }
    return (0);
}