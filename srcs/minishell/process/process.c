/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:10:12 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/01 19:45:55 by mvpee            ###   ########.fr       */
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

	if (data->nbr_cmd == 1)
	{
		builtins(head, data, parsing[0].cmd);
		return;
	}

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

	// if (data->nbr_cmd == 1 && !ft_strcmp(ft_split(parsing[0].cmd, " ")[0], "cd"))
	// {
	// 	builtins(head, data, parsing[0].cmd);
	// }
}
