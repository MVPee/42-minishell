/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:43:58 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/07 23:04:23 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_pipe(t_data *data, int i)
{
	int	j;

	j = -1;
	if (i < data->nbr_cmd - 1)
		dup2(data->pipefds[i][1], STDOUT_FILENO);
	if (i > 0)
		dup2(data->pipefds[i - 1][0], STDIN_FILENO);
	while (++j < data->nbr_cmd)
	{
		close(data->pipefds[j][0]);
		close(data->pipefds[j][1]);
	}
}

static void	ft_redirection(t_parsing parsing, t_data *data)
{
	int	pipe_heredoc[2];

	if (parsing.input != -1)
	{
		dup2(parsing.input, STDIN_FILENO);
		close(parsing.input);
	}
	else if (parsing.heredoc)
	{
		pipe(pipe_heredoc);
		write(pipe_heredoc[1], parsing.heredoc, ft_strlen(parsing.heredoc));
		close(pipe_heredoc[1]);
		dup2(pipe_heredoc[0], STDIN_FILENO);
		close(pipe_heredoc[0]);
	}
	if (parsing.output != -1)
	{
		dup2(parsing.output, STDOUT_FILENO);
		close(parsing.output);
	}
}

static void	ft_execve(t_parsing parsing, t_env **head, t_data *data, int i)
{
	if (parsing.path == NULL && !parsing.isbuiltins)
	{
		ft_printf_fd(2, "%s: command not found\n", parsing.cmd[0]);
		exit(127);
	}
	ft_pipe(data, i);
	ft_redirection(parsing, data);
	if (parsing.isbuiltins)
	{
		dup2(data->pipefds[i][1], STDOUT_FILENO);
		close(data->pipefds[i][1]);
		close(data->pipefds[i][0]);
		builtins(head, data, parsing);
		exit(0);
	}
	else
	{
		execve(parsing.path, parsing.cmd, env_to_tab(*head));
		perror(parsing.cmd[0]);
		if (errno == EACCES)
			exit(126);
		exit(1);
	}
}

void	child_process(t_env **head, t_data *data, t_parsing *parsing)
{
	int	i;

	i = -1;
	while (++i < data->nbr_cmd)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
		{
			perror("fork");
			return ;
		}
		if (data->pid[i] == 0)
		{
			if (parsing[i].cmd == NULL)
			{
				if (parsing[i].input != -1 || parsing[i].output != -1)
					exit(0);
				exit(1);
			}
			ft_execve(parsing[i], head, data, i);
		}
	}
}