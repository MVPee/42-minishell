/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 21:37:59 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/22 16:28:55 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_welcome_message(t_env *head)
{
	ft_printf(RED "\n\n	███╗   ███╗██╗███╗   ██╗██╗" RED BOLD "██╗  ██╗███████╗██╗     ██╗     \n" RESET);
	ft_printf(YELLOW "	████╗ ████║██║████╗  ██║██║" RED BOLD "██║  ██║██╔════╝██║     ██║     \n" RESET);
	ft_printf(GREEN "	██╔████╔██║██║██╔██╗ ██║██║" RED BOLD "███████║█████╗  ██║     ██║     \n" RESET);
	ft_printf(BLUE "	██║╚██╔╝██║██║██║╚██╗██║██║" RED BOLD "██╔══██║██╔══╝  ██║     ██║     \n" RESET);
	ft_printf(MAGENTA "	██║ ╚═╝ ██║██║██║ ╚████║██║" RED BOLD "██║  ██║███████╗███████╗███████╗\n" RESET);
	ft_printf(CYAN "	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝" RED BOLD "╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\n" RESET);
	ft_printf("SHLVL=%s\n", find_key(head, "SHLVL")->value);
}

char	*get_str_readline(void)
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
	//init_signal();
	print_welcome_message(head);
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
		t_cmd *cmd = parsing(line);
		// t_node *node;
		// while(cmd)
		// {
		// 	ft_printf("\n\ncmd: %s\n", cmd->cmd);
		// 	node = cmd->head;
		// 	while(node)
		// 	{
		// 		ft_printf("Token: %d; Name: %s\n", node->token, node->name);
		// 		node = node->next;
		// 	}
		// 	cmd = cmd->next;
		// }
		if (!builtins(&head, &data, cmd->cmd))
			process(head, &data, line);
		ft_free(1, &line);
		free_parsing(cmd);
	}
	free_env(head);
	//rl_clear_history();
	return (0);
}
