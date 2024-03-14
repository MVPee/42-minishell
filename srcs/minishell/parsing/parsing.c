/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:01:16 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/14 09:50:29 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	is_only_space(char *line)
{
	int	i;

	if (line[0] == '\'')
	{
		i = 0;
		while (line[++i] != '\'')
		{
			if ((line[i]) != ' ')
				return (false);
		}
	}
	else if (line[0] == '\"')
	{
		i = 0;
		while (line[++i] != '\"')
		{
			if ((line[i]) != ' ')
				return (false);
		}
	}
	else
		return (false);
	return (true);
}

static char	**ft_expand_space(char *str)
{
	int		len;
	char	*result;
	char	**split;

	split = NULL;
	result = NULL;
	len = ft_strlen(str) - 2;
	if (!len)
		return (ft_splitjoin(split, ""));
	while (len--)
		result = ft_strjoinchar_free(&result, ' ');
	split = ft_splitjoin(split, result);
	ft_free(1, &result);
	return (split);
}

static t_parsing	parsing_data(t_lexer lexer, t_data *data, t_env *env)
{
	t_parsing	parsing;

	parsing = init_parsing();
	if (!file_checker(&parsing, lexer, env, data))
		return (parsing);
	if (is_only_space(lexer.cmd))
	{
		parsing.cmd = ft_expand_space(lexer.cmd);
		parsing.path = NULL;
		return (parsing);
	}
	else
		parsing.cmd = ft_expand(lexer.cmd, env, *data);
	parsing.isbuiltins = isbuiltins(parsing.cmd[0]);
	parsing.ft_isspecial = ft_isspecial(parsing);
	parsing.path = path_checker(ft_split((const char *) \
		get_value(find_key(env, "PATH")), ":"), parsing);
	return (parsing);
}

t_parsing	*ft_parsing(t_lexer *lexer, t_data *data, t_env *env)
{
	t_parsing	*parsing;
	int			i;

	if (g_sig.flag)
	{
		g_sig.flag = false;
		data->env_var = 1;
	}
	if (!lexer)
		return (data->env_var = 2, NULL);
	parsing = malloc(sizeof(t_parsing) * data->nbr_cmd);
	if (!parsing)
		return (free_lexer(lexer, data->nbr_cmd), NULL);
	i = -1;
	while (++i < data->nbr_cmd)
	{
		parsing[i] = parsing_data(lexer[i], data, env);
		if (data->flag)
			return (free_lexer(lexer, data->nbr_cmd), ft_free(1, &parsing), \
				NULL);
		if (!parsing[i].cmd)
			return (free_lexer(lexer, data->nbr_cmd), free_parsing(parsing, \
					*data), NULL);
	}
	return (free_lexer(lexer, data->nbr_cmd), parsing);
}
