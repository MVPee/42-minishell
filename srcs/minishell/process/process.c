/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:10:12 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/01 20:19:42 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	process(t_env **head, t_data *data, t_parsing *parsing)
{
	int status;
	char *path;
	pid_t pid[data->nbr_cmd];
	int pipefds[data->nbr_cmd - 1][2];

	if (!parsing || !parsing->cmd)
		return ;

	// if (data->nbr_cmd == 1)
	// {
	// 	builtins(head, data, parsing[0].cmd);
	// 	return;
	// }

	for (int i = 0; i < data->nbr_cmd - 1; i++)
        pipe(pipefds[i]);

	for (int i = 0; i < data->nbr_cmd; i++)
	{
		pid[i] = fork();
		
		if (pid[i] == 0)
        {
            if (i < data->nbr_cmd - 1)
            	dup2(pipefds[i][1], STDOUT_FILENO);

            if (i > 0)
            	dup2(pipefds[i - 1][0], STDIN_FILENO);

            for (int j = 0; j < data->nbr_cmd - 1; j++)
            {
                close(pipefds[j][0]);
                close(pipefds[j][1]);
            }
			
			if (parsing[i].input != -1)
			{
				dup2(parsing[i].input, STDIN_FILENO);
				close(parsing[i].input);
			}
			else if (parsing[i].heredoc)
			{
				int pipe_heredoc[2];
				pipe(pipe_heredoc);
				write(pipe_heredoc[1], parsing[i].heredoc, ft_strlen(parsing[i].heredoc));
				close(pipe_heredoc[1]);
				dup2(pipe_heredoc[0], STDIN_FILENO);
				close(pipe_heredoc[0]);
			}
			
			if (parsing[i].output != -1)
			{
				dup2(parsing[i].output, STDOUT_FILENO);
				close(parsing[i].output);
			}

			if (parsing[i].isbuiltins)
			{
				dup2(pipefds[i][1], STDOUT_FILENO);
				close(pipefds[i][1]);
				close(pipefds[i][0]);
				builtins(head, data, parsing[i].cmd);
				exit(0);
			}
				
			else
			{
				char **split_cmd = ft_split(parsing[i].cmd, " ");
				execve(parsing[i].path, split_cmd, env_to_tab(*head));
				perror(parsing[i].cmd);
				exit(1);
			}
        }
	}

	for (int i = 0; i < data->nbr_cmd - 1; i++)
	{
        close(pipefds[i][0]);
        close(pipefds[i][1]);
    }

	for (int i = 0; i < data->nbr_cmd; i++)
        waitpid(pid[i], NULL, 0);

}
