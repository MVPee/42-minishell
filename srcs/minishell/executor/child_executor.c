/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:43:58 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/14 15:40:05 by mvpee            ###   ########.fr       */
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

static void	ft_redirection(t_parsing parsing)
{
	if (parsing.input != -1)
	{
		dup2(parsing.input, STDIN_FILENO);
		close(parsing.input);
	}
	if (parsing.output != -1)
	{
		dup2(parsing.output, STDOUT_FILENO);
		close(parsing.output);
	}
}

static void	ft_execve_check(t_parsing parsing)
{
	if (parsing.path == NULL && !parsing.isbuiltins)
	{
		if (ft_ischarin('/', parsing.cmd[0]))
			ft_printf_fd(2, "%s: No such file or directory\n", parsing.cmd[0]);
		else
			ft_printf_fd(2, "%s: command not found\n", parsing.cmd[0]);
		exit(127);
	}
	if (parsing.flag)
		exit(1);
}

static void	ft_execve(t_parsing parsing, t_env **head, t_data *data, int i)
{
	char	**env;

	env = env_to_tab(*head);
	ft_execve_check(parsing);
	ft_pipe(data, i);
	ft_redirection(parsing);
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
		execve(parsing.path, parsing.cmd, env);
		perror(parsing.cmd[0]);
		ft_free_matrix(1, &env);
		if (errno == EACCES)
			exit(MISSING_RIGHTS);
		exit(1);
	}
}

void	child_executor(t_env **head, t_data *data, t_parsing *parsing)
{
	int	i;

	i = -1;
	if (!ft_strcmp(parsing->cmd[0], EXECUTABLE_NAME))
		g_sig.minishell = true;
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
			signal(SIGINT, SIG_DFL);
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
