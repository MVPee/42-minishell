/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:10:12 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/11 16:22:47 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	init_process(t_data *data)
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

static void	free_process(t_parsing *parsing, t_data *data)
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
		waitpid(data->pid[i], &status, 0);
	if (WIFEXITED(status))
		data->env_var = WEXITSTATUS(status);
	else
		data->env_var = 130;
}

void	process(t_env **head, t_data *data, t_parsing *parsing)
{
	int	i;

	if (!parsing)
		return ;
	if (init_process(data))
		return ;
	if (data->nbr_cmd == 1 && parsing[0].isspecial)
	{
		builtins(head, data, parsing[0]);
		return ;
	}
	i = -1;
	while (++i < data->nbr_cmd)
		pipe(data->pipefds[i]);
	child_process(head, data, parsing);
	i = -1;
	while (++i < data->nbr_cmd)
	{
		close(data->pipefds[i][0]);
		close(data->pipefds[i][1]);
	}
	ft_waitpid(data);
	free_process(parsing, data);
}
