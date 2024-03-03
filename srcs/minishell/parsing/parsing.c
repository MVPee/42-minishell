/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:01:16 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/03 15:27:12 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_open(char *file, t_token token)
{
	if (token == INPUT)
		return (open(file, O_RDONLY));
	else if (token == OUTPUT)
		return (open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	else if (token == APPEND)
		return (open(file, O_CREAT | O_APPEND | O_WRONLY, 0644));
	return (-1);
}

bool	check_file(t_parsing *parsing, t_lexer lexer)
{
	t_node	*node;
	char	*temp;
	char	*temp_cmd;

	node = NULL;
	node = lexer.head;
	while (node)
	{
		if (node->token == INPUT)
		{
			if (parsing->heredoc)
			{
				free(parsing->heredoc);
				parsing->heredoc = NULL;
			}
			if (parsing->input != -1)
				close(parsing->input);
			parsing->input = ft_open(node->name, INPUT);
			if (parsing->input == -1)
			{
				perror(node->name);
				return (false);
			}
		}
		else if (node->token == OUTPUT || node->token == APPEND)
		{
			if (parsing->output != -1)
				close(parsing->output);
			parsing->output = ft_open(node->name, node->token);
			if (parsing->output == -1)
			{
				perror(node->name);
				return (false);
			}
		}
		else if (node->token == HEREDOC)
		{
			parsing->heredoc = ft_heredoc(node->name);
			if (!parsing->heredoc)
			{
				perror("Memory allocation error");
				return (false);
			}
			close(parsing->input);
			parsing->input = -1;
		}
		node = node->next;
	}
	return (true);
}

t_parsing init_parsing()
{
	t_parsing parsing;

	parsing.cmd = NULL;
	parsing.cmd_args = NULL;
	parsing.input = -1;
	parsing.output = -1;
    parsing.isbuiltins = false;
	parsing.heredoc = NULL;
	parsing.path = NULL;
	return (parsing);
}

t_parsing *ft_parsing(t_lexer *lexer, t_data *data, t_env *env)
{
    t_parsing *parsing;
	int i;

	if (!lexer)
        return (data->env_var = 2, NULL);
	parsing = malloc(sizeof(t_parsing) * data->nbr_cmd);
	if (!parsing)
		return (free_lexer(lexer), NULL);
	i = -1;
    while (++i < data->nbr_cmd)
    {
        parsing[i] = init_parsing();
        if (!check_file(&parsing[i], lexer[i]))
            return (data->env_var = 1, NULL);
		if (ft_strcmp(lexer[i].cmd, ""))
		{
			if (!ft_strcmp(ft_split(lexer[i].cmd, " ")[0], "export"))
				parsing[i].cmd = ft_strdup(lexer[i].cmd);
			else
				parsing[i].cmd = checker(lexer[i].cmd, env, *data);
			parsing[i].cmd_args = get_args(lexer[i].cmd, env, *data);
			if (!(parsing[i].path = path_checker(ft_split((const char *)get_value(find_key(env, "PATH")), ":"), ft_split(parsing[i].cmd, " ")[0])))
				if (isbuiltins(parsing[i].cmd))
					parsing[i].isbuiltins = true;
		}
    }
	free_lexer(lexer);
    return (parsing);
}
