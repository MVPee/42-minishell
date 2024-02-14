/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:37:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/14 10:37:03 by mvan-pee         ###   ########.fr       */
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

static void process(t_env *head, t_data *data, char *line)
{
	(void)head;
	char **split = ft_split(line, " ");
	if (!ft_strcmp(split[0], "echo"))
		ft_echo(data, split);
	// else if(!ft_strcmp(split[0], "cd"))
	// 	ft_cd(env, split);
	else
		ft_printf("%s: command not found\n", line);
	ft_free_matrix(1, &split);
}

int	main(int ac, char **argv, char **envs)
{
	t_env *head;
	t_data data;
	char	*line;
	char	*str_readline;

	data.env_var = 0;
	head = env_init(envs);
	find_key(head, "PWD");
	line = NULL;
	while (1)
	{
		str_readline = get_str_readline(head);
		line = readline(str_readline);
		ft_free(1, &str_readline);
		if (!ft_strcmp(line, "exit"))
		{
			free(line);
			break ;
		}
		process(head, &data, line);
		free(line);
	}
	return (0);
}
