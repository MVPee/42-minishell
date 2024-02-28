/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:10:12 by mvpee             #+#    #+#             */
/*   Updated: 2024/02/28 18:52:39 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*find_executable_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*temp;

	if (!paths || !cmd)
		return (NULL);
	if (cmd[0] == '.' && cmd[1] == '/')
		return (ft_free_matrix(1, &paths), NULL);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (ft_free_matrix(1, &paths), NULL);
		path = ft_strjoin(temp, cmd);
		if (!path)
			return (ft_free_matrix(1, &paths), ft_free(1, &temp), NULL);
		if (access(path, F_OK) == 0)
			return (ft_free_matrix(1, &paths), ft_free(1, &temp), path);
		ft_free(2, &path, &temp);
	}
	ft_free_matrix(1, &paths);
	return (NULL);
}

void	process(t_env **head, t_data *data, t_parsing *parsing)
{
	int status;
	char *path;
	pid_t pid;
	int pipe_builtin_to_next[2];
	int prev_pipe[2] = {-1, -1};
	int curr_pipe[2] = {-1, -1};

	if (!parsing || !parsing->cmd)
		return ;
	while (parsing)
	{
		if (parsing->next)
		{
			if (pipe(curr_pipe) == -1)
			{
				perror("pipe");
				exit(1);
			}
		}
		if (parsing->isbuiltins == true)
		{
			data->temp = builtins(head, data, parsing->cmd, parsing->next);
			if (parsing->output != -1 && data->temp)
				write(parsing->output, data->temp, ft_strlen(data->temp));
			else if (parsing->output == -1 && data->temp && !parsing->next)
				ft_printf("%s", data->temp);
		}
		else
		{
			path = find_executable_path(ft_split((const char *)get_value(find_key(*head, "PATH")), ":"), ft_split(parsing->cmd, " ")[0]);
			if (!path)
			{
				char buffer[500];
				path = ft_strjoin(getcwd(buffer, 500), ft_strtrim(parsing->cmd, ". "));
			}
			if (access(path, F_OK) == 0)
			{
				pid = fork();
				if (pid == -1)
				{
					perror("fork");
					exit(EXIT_FAILURE);
				}
				else if (pid == 0)
				{
					if (prev_pipe[0] != -1)
					{
						if (dup2(prev_pipe[0], STDIN_FILENO) == -1)
						{
							perror("dup2 stdin");
							exit(EXIT_FAILURE);
						}
						close(prev_pipe[0]);
						close(prev_pipe[1]);
					}

					if (parsing->input != -1)
					{
						if (dup2(parsing->input, STDIN_FILENO) == -1)
						{
							perror("dup2 input");
							exit(EXIT_FAILURE);
						}
						close(parsing->input);
					}
					else if (parsing->heredoc)
					{
						int pipe_heredoc[2];
						if (pipe(pipe_heredoc) == -1)
						{
							perror("pipe");
							exit(EXIT_FAILURE);
						}
						write(pipe_heredoc[1], parsing->heredoc, ft_strlen(parsing->heredoc));
						close(pipe_heredoc[1]);
						if (dup2(pipe_heredoc[0], STDIN_FILENO) == -1)
						{
							perror("dup2 heredoc");
							exit(EXIT_FAILURE);
						}
						close(pipe_heredoc[0]); 
					}
					else if (data->temp)
					{
						if (pipe(pipe_builtin_to_next) == -1)
						{
							perror("pipe");
							exit(EXIT_FAILURE);
						}
						if (write(pipe_builtin_to_next[1], data->temp, ft_strlen(data->temp)) == -1)
						{
							perror("write to pipe");
							exit(EXIT_FAILURE);
						}
						close(pipe_builtin_to_next[1]);
						if (dup2(pipe_builtin_to_next[0], STDIN_FILENO) == -1)
						{
							perror("dup2 for builtin output");
							exit(EXIT_FAILURE);
						}
					}
					if (parsing->next)
					{
						if (dup2(curr_pipe[1], STDOUT_FILENO) == -1)
						{
							perror("dup2 stdout");
							exit(EXIT_FAILURE);
						}
						close(curr_pipe[0]);
					}

					if (parsing->output != -1)
					{
						if (dup2(parsing->output, STDOUT_FILENO) == -1)
						{
							perror("dup2 output");
							exit(EXIT_FAILURE);
						}
						close(parsing->output);
					}
					execve(path, ft_split(parsing->cmd, " "), env_to_tab(*head));
					perror(parsing->cmd);
					exit(EXIT_FAILURE);
				}
				else
				{ // Parent process
					close(pipe_builtin_to_next[0]);
					if (prev_pipe[0] != -1)
					{
						close(prev_pipe[0]);
						close(prev_pipe[1]);
					}
					if (waitpid(pid, &status, 0) == -1)
					{
						perror("waitpid");
						exit(EXIT_FAILURE);
					}

					if (WIFEXITED(status))
						data->env_var = WEXITSTATUS(status);
					prev_pipe[0] = curr_pipe[0];
					prev_pipe[1] = curr_pipe[1];
					curr_pipe[0] = -1;
					curr_pipe[1] = -1;
					if (data->temp != NULL)
						ft_free(1, &data->temp);
				}
			}
			else
			{
				ft_printf("%s: command not found\n", parsing->cmd);
				data->env_var = 127;
			}
		}
		parsing = parsing->next;
	}
	if (prev_pipe[0] != -1)
	{
		close(prev_pipe[0]);
		close(prev_pipe[1]);
	}
}
