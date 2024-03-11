/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:01:16 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/11 16:31:53 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_parsing	parsing_data(t_lexer lexer, t_data *data, t_env *env, int i)
{
	t_parsing	parsing;

	parsing = init_parsing();
	if (!file_checker(&parsing, lexer, env, data))
		return (parsing);
	if (data->flag)
		return (parsing);
	if (ft_strcmp(lexer.cmd, ""))
	{
		parsing.cmd = ft_expand(lexer.cmd, env, *data);
		if (!parsing.cmd)
			return (parsing);
		parsing.isbuiltins = isbuiltins(parsing.cmd[0]);
		parsing.isspecial = isspecial(parsing);
		parsing.path = path_checker(ft_split((const char *)get_value(find_key \
			(env, "PATH")), ":"), parsing);
	}
	return (parsing);
}

t_parsing	*ft_parsing(t_lexer *lexer, t_data *data, t_env *env)
{
	t_parsing	*parsing;
	int			i;

	if (!lexer)
		return (data->env_var = 2, NULL);
	parsing = malloc(sizeof(t_parsing) * data->nbr_cmd);
	if (!parsing)
		return (free_lexer(lexer), NULL);
	i = -1;
	while (++i < data->nbr_cmd)
	{
		parsing[i] = parsing_data(lexer[i], data, env, i);
		if (!parsing[i].cmd || data->flag)
			return (free_lexer(lexer), free_parsing(parsing, *data), NULL);
	}
	return (free_lexer(lexer), parsing);
}
