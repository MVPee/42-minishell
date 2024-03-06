/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:01:16 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/06 09:53:10 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_open(char *file, t_token token)
{
	if (token == INPUT)
		return (open(file, O_RDONLY));
	else if (token == OUTPUT)
		return (open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	else if (token == APPEND)
		return (open(file, O_CREAT | O_APPEND | O_WRONLY, 0644));
	return (-1);
}

static bool	check_file(t_parsing *parsing, t_lexer lexer, t_env *env, t_data data)
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
			parsing->heredoc = ft_heredoc(node->name, env, data);
			if (!parsing->heredoc)
				return (false);
			close(parsing->input);
			parsing->input = -1;
		}
		node = node->next;
	}
	return (true);
}

static t_parsing init_parsing()
{
	t_parsing parsing;

	parsing.cmd = NULL;
	parsing.input = -1;
	parsing.output = -1;
    parsing.isbuiltins = false;
	parsing.isspecial = false;
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
        if (!check_file(&parsing[i], lexer[i], env, *data))
        {
			data->env_var = 1;
			ft_free(1, &lexer[i].cmd);
			lexer[i].cmd = ft_strdup("");
		}
		if (ft_strcmp(lexer[i].cmd, ""))
		{
			parsing[i].cmd = parsing_cmd(lexer[i].cmd, env, *data), " ";
			if (!parsing[i].cmd)
				return (free_lexer(lexer), NULL);
			parsing[i].isbuiltins = isbuiltins(parsing[i].cmd[0]);
			parsing[i].isspecial = isspecial(parsing[i]);
			parsing[i].path = path_checker(ft_split((const char *)get_value(find_key(env, "PATH")), ":"), parsing[i].cmd[0]);
		}
    }
	free_lexer(lexer);
    return (parsing);
}
