/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:37:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/12 19:04:11 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

void	extract_int(char *env, t_env *env_vars, char **splitted_env)
{
	if (!ft_strncmp(env, "SHLVL", 5))
	{
		splitted_env = ft_split(env, "=");
		env_vars->shell_level = ft_atoi(splitted_env[1]);
		ft_free_matrix(1, &splitted_env);
	}	
}

void	extract_str(char *env, t_env *env_vars, char **splitted_env)
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

t_env	ft_extract_env(char **env)
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

int main(int ac, char **argv, char **env)
{
    char *line = NULL;
	
	t_env test = ft_extract_env(env);
	// int i = 0;
	// while (test->path[i])
	// {
	// 	ft_printf("PATH %s\n", test->path[i]);
	// 	i++;
	// }
	ft_printf("PWD %s\n", test.pwd);
	// ft_printf("SHELL LEVEL %d\n", test->shell_level);
	// while (*env)
	// 	ft_printf("%s\n", *env++);

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