/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:18:05 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/13 09:20:33 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_lexer	set_lexer(char *str, t_env *env, t_data data)
{
	t_lexer	new_lexer;
	int		i;
	char	*buffer;
	char	*file_name;
	char 	**split_temp;

	new_lexer.cmd = NULL;
	new_lexer.head = NULL;
	buffer = NULL;
	file_name = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
		{
			buffer = ft_strjoinchar_free(&buffer, str[i]);
			while (str[i] != '\"' && str[i])
				buffer = ft_strjoinchar_free(&buffer, str[i++]);
			buffer = ft_strjoinchar_free(&buffer, str[i]);
		}
		else if (str[i] == '\'')
		{
			buffer = ft_strjoinchar_free(&buffer, str[i++]);
			while (str[i] != '\'' && str[i])
				buffer = ft_strjoinchar_free(&buffer, str[i++]);
			buffer = ft_strjoinchar_free(&buffer, str[i]);
		}
		else if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
			{
				i++;
				while (str[i] == ' ')
					i++;
				while (str[i] != ' ' && str[i])
				{
					if (str[i] == '\'')
					{
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
						while (str[i] != '\'' && str[i])
							file_name = ft_strjoinchar_free(&file_name, str[i++]);
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
					}
					else if (str[i] == '\"')
					{
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
						while (str[i] != '\"' && str[i])
							file_name = ft_strjoinchar_free(&file_name, str[i++]);
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
					}
					else
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
				}
				append_node(&(new_lexer.head), file_name, HEREDOC);
				ft_free(1, &file_name);
			}
			else
			{
				while (str[i] == ' ')
					i++;
				while (str[i] != ' ' && str[i])
				{
					if (str[i] == '\'')
					{
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
						while (str[i] != '\'' && str[i])
							file_name = ft_strjoinchar_free(&file_name, str[i++]);
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
					}
					else if (str[i] == '\"')
					{
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
						while (str[i] != '\"' && str[i])
							file_name = ft_strjoinchar_free(&file_name, str[i++]);
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
					}
					else
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
				}
				if (!ft_strcmp(file_name, "\'\'") || !ft_strcmp(file_name, "\"\""))
					append_node(&(new_lexer.head), "", INPUT);
				else
				{
					split_temp = ft_expand(file_name, env, data);
					append_node(&(new_lexer.head), split_temp[0], INPUT);
					ft_free_matrix(1, &split_temp);
				}
				ft_free(1, &file_name);
			}
			i--;
		}
		else if (str[i] == '>')
		{
			i++;
			if (str[i] == '>')
			{
				i++;
				while (str[i] == ' ')
					i++;
				while (str[i] != ' ' && str[i])
				{
					if (str[i] == '\'')
					{
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
						while (str[i] != '\'' && str[i])
							file_name = ft_strjoinchar_free(&file_name, str[i++]);
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
					}
					else if (str[i] == '\"')
					{
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
						while (str[i] != '\"' && str[i])
							file_name = ft_strjoinchar_free(&file_name, str[i++]);
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
					}
					else
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
				}
				if (!ft_strcmp(file_name, "\'\'") || !ft_strcmp(file_name, "\"\""))
					append_node(&(new_lexer.head), "", APPEND);
				else
				{
					split_temp = ft_expand(file_name, env, data);
					append_node(&(new_lexer.head), split_temp[0], APPEND);
					ft_free_matrix(1, &split_temp);
				}
				ft_free(1, &file_name);
			}
			else
			{
				while (str[i] == ' ')
					i++;
				while (str[i] != ' ' && str[i])
				{
					if (str[i] == '\'')
					{
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
						while (str[i] != '\'' && str[i])
							file_name = ft_strjoinchar_free(&file_name, str[i++]);
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
					}
					else if (str[i] == '\"')
					{
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
						while (str[i] != '\"' && str[i])
							file_name = ft_strjoinchar_free(&file_name, str[i++]);
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
					}
					else
						file_name = ft_strjoinchar_free(&file_name, str[i++]);
				}
				if (!ft_strcmp(file_name, "\'\'") || !ft_strcmp(file_name, "\"\""))
					append_node(&(new_lexer.head), "", OUTPUT);
				else
				{
					split_temp = ft_expand(file_name, env, data);
					append_node(&(new_lexer.head), split_temp[0], OUTPUT);
					ft_free_matrix(1, &split_temp);
				}
				ft_free(1, &file_name);
			}
			i--;
		}
		else
			buffer = ft_strjoinchar_free(&buffer, str[i]);
		if (!str[i])
			break ;
	}
	new_lexer.cmd = buffer;
	return (new_lexer);
}

t_lexer	*ft_lexer(char *line, t_data *data, t_env *env)
{
	char	**split;
	t_lexer	*lexer;
	int		count;
	int		i;

	count = 0;
	lexer = NULL;
	if (!line)
		return (NULL);
	if (!ft_strcmp(line, "\0"))
		return (ft_free(1, &line), NULL);
	if (syntax_check(line))
		return (ft_free(1, &line), NULL);
	split = ft_splittrim(get_cmd_splitted(line, &count), " ");
	if (!split)
		return (ft_free(1, &line), NULL);
	lexer = malloc(sizeof(t_lexer) * count);
	if (!lexer)
		return (ft_free(1, &line), NULL);
	data->nbr_cmd = count;
	i = -1;
	while (++i < count)
		lexer[i] = set_lexer(split[i], env, *data);
	return (ft_free_matrix(1, &split), ft_free(1, &line), lexer);
}
