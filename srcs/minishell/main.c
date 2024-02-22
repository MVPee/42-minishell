/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nechaara <nechaara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:37:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/22 14:45:43 by nechaara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_str_readline(void)
{
	char	*temp;
	char	*str_pwd;
	char	*str_readline;
	char	buffer[500];

	temp = ft_strjoin(YELLOW BOLD, getcwd(buffer, 500));
	str_pwd = ft_strjoin(temp, RESET);
	ft_free(1, &temp);
	temp = ft_strjoin(RED BOLD "minihell " RESET, str_pwd);
	str_readline = ft_strjoin(temp, "$ ");
	ft_free(2, &str_pwd, &temp);
	return (str_readline);
}

int	main(int ac, char **argv, char **envs)
{
	t_env	*head;
	t_data	data;
	char	*line;
	char	*str_readline;

	data.env_var = 0;
	head = env_init(envs);

	line = NULL;
	while (1)
	{
		str_readline = get_str_readline();
		line = readline(str_readline);
		ft_free(1, &str_readline);
		if (ft_strcmp(line, "\0"))
			add_history(line);
		else
			data.env_var = 0;
		if (!ft_strcmp(line, "exit"))
		{
			ft_free(1, &line);
			ft_printf("exit\n");
			break ;
		}
		if (!builtins(&head, &data, line))
			process(head, &data, line);
		ft_free(1, &line);
	}
	rl_clear_history();
	free_env_list(head);
	return (0);
}
