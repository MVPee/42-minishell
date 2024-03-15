/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-pee <mvan-pee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:10:12 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/15 15:07:15 by mvan-pee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	init_executor(t_data *data)
{
	int	i;

	data->pid = malloc(sizeof(pid_t) * (data->nbr_cmd));
	if (!data->pid)
		return (true);
	data->pipefds = malloc(sizeof(int *) * (data->nbr_cmd));
	if (!data->pipefds)
		return (ft_free(1, &data->pid), true);
	i = -1;
	while (++i < data->nbr_cmd)
	{
		data->pipefds[i] = malloc(sizeof(int) * 2);
		if (!data->pipefds[i])
		{
			ft_free(1, &data->pid);
			ft_free_matrix(1, &data->pipefds);
			return (true);
		}
	}
	return (false);
}

static void	free_executor(t_parsing *parsing, t_data *data)
{
	int	i;

	i = -1;
	ft_free(1, &data->pid);
	while (++i < data->nbr_cmd)
		ft_free(1, &data->pipefds[i]);
	ft_free(1, &data->pipefds);
	free_parsing(parsing, *data);
}

static void	ft_waitpid(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (++i < data->nbr_cmd)
	{
		close(data->pipefds[i][0]);
		close(data->pipefds[i][1]);
	}
	i = -1;
	while (++i < data->nbr_cmd)
		waitpid(data->pid[i], &status, 0);
	if (WIFEXITED(status))
		data->env_var = WEXITSTATUS(status);
	else if (g_sig.flag == SIGQUIT)
	{
		g_sig.flag = 0;
		data->env_var = 131;
	}
	else
		data->env_var = COMMAND_INTERRUPTED;
}

static bool	ft_pipe(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_cmd)
	{
		if (pipe(data->pipefds[i]) == -1)
		{
			perror("pipe");
			return (false);
		}
	}
	return (true);
}

void	executor(t_env **head, t_data *data, t_parsing *parsing)
{
	if (data->flag)
	{
		data->flag = false;
		return ;
	}
	if (!parsing || init_executor(data))
		return ;
	if (data->nbr_cmd == 1 && parsing[0].ft_isspecial)
	{
		builtins(head, data, parsing[0]);
		free_executor(parsing, data);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	if (ft_strcmp(parsing[0].cmd[0], EXECUTABLE_NAME))
		signal(SIGQUIT, signal_quit);
	if (ft_pipe(data))
	{
		child_executor(head, data, parsing);
		ft_waitpid(data);
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	free_executor(parsing, data);
}
