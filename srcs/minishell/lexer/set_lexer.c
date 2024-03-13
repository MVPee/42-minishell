/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvpee <mvpee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:38:20 by mvpee             #+#    #+#             */
/*   Updated: 2024/03/13 09:38:41 by mvpee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_lexer	set_lexer(char *str, t_env *env, t_data data)
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
				append_node(&(new_lexer.head), file_name, OUTPUT);
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
				append_node(&(new_lexer.head), file_name, OUTPUT);
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
				append_node(&(new_lexer.head), file_name, OUTPUT);
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
